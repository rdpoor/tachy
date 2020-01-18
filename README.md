# tachy
Implement a speedometer using vibration sensing and signal processing.

`tachy` (pronounced "TAK-ee") is a microprocessor-based speedometer designed for vehicles with two axles.
Using an accelerometer to sense vibration in the wheels as the vehicle moves, it feeds the signal to an 
autocorrelation algorithm to estimate the vehicle's speed.

`tachy` was originally designed as a somewhat silly technique to measure speed.  But since it doesn't require 
any modifications or permanent attachments to the vehicle, it may be a useful solution for some applications.

## How it works

tachy continually digitizes a road noise using an accelerometer and writes the results into a circular buffer.  
It uses a simple autocorrelation routine to find the delay between road noise contributed by the front wheels to 
the same road noise contributed by the rear wheels and converts that to a speed measurement.

## About resolution and minimum speed

The spacing between the two axles, the sampling rate and the size of the circular buffer determine the
resolution and minimum speed that `tachy` is able to measure.  Before launching into the derivation, the 
following table gives some insights:

|miles/hour|km/hour|meters/second|
|--|--|--|
|0.6213|1|0.278|
|1.864|3|0.833|
|5.592|9|2.5|
|16.78|27|7.5|
|50.33|81|22.5|
|100.7|162|45|

As an example, assume we are configuring `tachy` for a car with a wheelbase of 2.7 meters.

The sampling rate determines the highest speed we can resolve.  If our car with its wheelbase
of 2.7 meters is traveling 45 meters per second (i.e. about 100 miles per hour or 162 km/hour),
then the rear wheel will be in the same spot on the road that the front wheel was 60 milliseconds
earlier.  In other words, if there was a small bump in the road, our sampled signal would contain
two small peaks, 60 milliseconds apart.

In order to get good resolution, we want take at least ten samples between those two
events, so our sampling interval must be 6 milliseconds or 167 samples/second.

What about the lowest speed we can measure?  For the corrlation algorithm to work properly,
our circular buffer must be long enough to hold twice the number of samples between "front 
bump" and "rear bump".  If the lowest speed we're interested in is 2.5 meters/second (i.e. 
5.6 miles per hour or 9 km/hour), then 1.08 seconds will elapse between "front bump" and 
"rear bump".  With a sampling rate of 167 samples/second, then we need 2 * 167 * 2.7 / 2.5 
samples = 361 samples.

Rather than make our buffer 361 samples long, we might as well splurge and round our buffer
up to the nearest power of two, or 512 samples -- this simplifies updating the indeces for
our circular buffer.  With a 512 sample buffer, we can measure speeds as low as 1.76 meters
per second (i.e. 3.94 miles/hour or 6.34 km/hour).
