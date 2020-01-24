# tachy
Implement a speedometer using vibration sensing and signal processing.

`tachy` (pronounced "TAK-ee") is a microprocessor-based speedometer designed for vehicles with two axles. Using an accelerometer to sense vibration in the wheels
as the vehicle moves, it feeds the signal to an autocorrelation algorithm to
estimate the vehicle's speed.

`tachy` was originally designed as a somewhat whimsical technique to measure
speed.  But since it doesn't require any wiring or permanent modifications
to the vehicle, it may be a useful approach for some applications.

## How it works

tachy continually digitizes a road noise using an accelerometer and writes the
results into a circular buffer.  It uses a simple autocorrelation routine to
find the delay between road noise contributed by the front wheels to the same
road noise contributed by the rear wheels and converts that to a speed
measurement.

## About resolution and minimum speed

The spacing between the two axles, the sampling rate and the size of the
circular buffer determine the resolution and minimum speed that `tachy` is able
to measure.  Before launching into the derivation, the following table gives
some insights:

|miles/hour|km/hour|meters/second|
|--|--|--|
|0.6213|1|0.278|
|1.864|3|0.833|
|5.592|9|2.5|
|16.78|27|7.5|
|50.33|81|22.5|
|100.7|162|45|

As an example, assume we are configuring `tachy` for a car with a wheelbase of
2.7 meters.

The sampling rate determines the highest speed we can resolve.  If our car with
its wheelbase of 2.7 meters is traveling 45 meters per second (i.e. about 100
miles per hour or 162 km/hour), then the rear wheel will be in the same spot on
the road that the front wheel was 60 milliseconds earlier.  In other words, if
there was a small bump in the road, our sampled signal would contain two small
peaks, 60 milliseconds apart.

In order to get good resolution, we want take at least ten samples between those
two events, so our sampling interval must be 6 milliseconds or 167 samples per
second.

What about the lowest speed we can measure?  For the correlation algorithm to
work properly, our circular buffer must be long enough to hold twice the number
of samples between "front bump" and "rear bump".  If the lowest speed we're
interested in is 2.5 meters/second (i.e. 5.6 miles per hour or 9 km/hour), then
1.08 seconds will elapse between "front bump" and "rear bump".  With a sampling
rate of 167 samples/second, then we need 2 * 167 * 2.7 / 2.5 samples = 361
samples.

Rather than make our buffer 361 samples long, we might as well round our buffer
up to the nearest power of two, or 512 samples -- this simplifies updating the
indeces for our circular buffer.  With a 512 sample buffer, we can measure
speeds as low as 1.76 meters per second (i.e. 3.94 miles/hour or 6.34 km/hour).

## Implentation Parameters

The ADXL can sample at 100, 200, 400 samples per second.  From the above, we
choose 200 samples per second and a buffer length of 512.

With a window size of 256 samples, a full autocorrelation operation requires
256^2 = 65K integer multiplies.  Since we can't have the buffer changing out
from under us (unless we extend the circular buffer size), we need to complete
the operation before the FIFO overflows.  With a 32 word fifo and asampling rate
of 200 Hz, that gives us 32 / 200 = 160 milliseconds to complete the cycle.
(In practice, is will be much less, since we need to fetch samples via I2c,
find the maximum, translate into velocity and update the LCD display.)

A dummy autocorrelation function with a window size of 256 samples using
int32_t samples takes 25 milliseconds to complete, so it appears we'll have
plenty of time.

## Design notes

### Sampling the accelerometer

For the autocorrelation algorithm to work properly, we need a steady flow of
samples taken at a constant rate.

The ADXL345 has an internal FIFO and will raise its interrupt line only when
the FIFO exceeds a programmable high water mark.  

But we may not need to use interrupts at all.  Set the sampling rate, enable
the FIFO, and check the # of samples available from within the main processing
loop.  Fetch as many samples as available, then run the autocorrelation
algorithm.

If the algorithm takes too long, then the FIFO will overflow.  But if that's
the case, no amount of buffering or interrupt level processing will make any
difference.

We could use the interrupt line as an efficient way to find out if there are
samples available: reading a GPIO line is much faster than doing an I2C read
operation to read the FIFO status register.  But that's an optimization.

### Accuracy

Since we're depending on the internal sampling rate of the ADXL345 as our
timing reference, it's useful to know its accuracy.  This note:

    https://ez.analog.com/mems/f/q-a/81963/how-accurate-is-adxl345-internal-oscillator
    https://ez.analog.com/mems/f/q-a/115164/adxl345-internal-clock-ppm

suggests that it's about +/- 2% accurate.  We could squeeze more accuracy out of
it by measuring it against the 32KHz crystal oscillator that comes with the
SAML22 Xplained Pro board.  See the note above on how to test the ADXL345 clock
frequency.

### Resetting the accelerometer

It appears that in some cases, the accelerometer can get into an error state
and report that zero samples are available.  Need to research what it takes to
do a full reset of the device.

### Optimizations:

Possible optimizations, if needed:

Currently, we fetch and convert data for all three axes.  If our routine uses
only one axis, we can save time in fetching and converting.  (Question: if you
read only one axis from the FIFO, does it free up the other two?)

Since the accelerometer output is signed 10 bit integer, we could run the
inner loop of the correlator using fixpoint.  With a buffer of 512 samples, the
autocorrelation algorithm sums the product of 256 samples.  The maximum sample
has a magnitude of 2^9, so the maximum product of any two samples is 2^10.
Summing that 256 times gives us a maximum sum of 2^18, which fits (easily) in
a 32 bit integer.

As noted above, we could use a GPIO line to detect data available rather than
performing an I2C read operation.

If we have locked onto the current speed, we can start the search for maximum
correlation in the vicinity of that speed.  This way we don't need to find the
maximum across all 256 steps.

By pulling CS to ground, the ADXL345 will use SPI protocols instead of I2C.  This
would allow sample data to be fetch much faster.  But this may not be the
limiting factor.

### The sample buffer

We have a circular buffer that's 512 samples long.  The oldest samples is at
get_sample(0), the newest is at get_sample(SAMPLE_BUF_SIZE-1);

    #define SAMPLE_BUF_SIZE 512
    #define WINDOW_SIZE (SAMPLE_BUF_SIZE / 2)

    static int32_t sample_buf[SAMPLE_BUF_SIZE];
    static int s_sample_index;

    int32_t get_sample(int index) {
      return buf[(s_sample_index + index) % SAMPLE_BUF_SIZE];
    }

    void put_sample(int32_t sample) {
      sample_buf[s_sample_index++] = sample;
      if (s_sample_index >= SAMPLE_BUF_SIZE) {
        s_sample_index %= SAMPLE_BUF_SIZE;
      }
    }

    int32_t autocorr_aux(int offset) {
      int32_t total = 0;
      for (int i=0; i<WINDOW_SIZE; i++) {
        int32_t a = get_sample(i);
        int32_t b = get_sample(i+offset);
        total += a * b;
      }
      return total;
    }

    int autocorrelate() {
      int32_t max_corr = autocorr_aux(MIN_OFFSET);
      int max_offset = MIN_OFFSET;
      for (int offset=MIN_OFFSET+1; offset<WINDOW_SIZE; offset++) {
        int32_t corr = autocorr_aux(offset);
        if (corr > max_corr) {
          max_corr = corr;
          max_offset = offset;
        }
      }
      return max_offset;
    }
