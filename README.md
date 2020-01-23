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

## Design notices

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

### Resetting the accelerometer

It appears that in some cases, the accelerometer can get into an error state
and report that zero samples are available.  Need to research what it takes to
do a full reset of the device.
