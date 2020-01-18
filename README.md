# tachy
Use a microphone and some signal processing to create a speedometer

`tachy` (pronounced "TAK-ee") is a microprocessor-based speedometer designed for vehicles with two axles.
It uses a microphone to measure the road noise as the vehicle moves, feeding the signal to an autocorrelation 
algorithm to estimate the vehicle's speed.

Although tachy was originally designed as a fun experiment, it may find a practical use since it doesn't
require any modifications or permanent attachments to the vehicle.

## How it works

tachy continually digitizes a road noise using a microphone and writes the results into acircular buffer.  
It uses a simple autocorrelation routine to find the delay between road noise contributed by the front tires to 
the same road noise contributed by the rear tires.

## About resolution and minimum speed

The spacing between the two axles, the sampling rate and the size of the circular buffer determine 
the resolution and minimum speed that `tachy` is able to measure.  Before launching into the theory, 
the following table helps give some insights:

|miles/hour|km/hour|meters/second|
|--|--|--|
|0.6213|1|0.278|
|1.864|3|0.833|
|5.592|9|2.5|
|16.78|27|7.5|
|50.33|81|22.5|
|100.7|162|45|

So as one example, assume we are configuring `tachy` for a car with a wheelbase of 2.7 meters.

The sampling rate determines the highest speed we can resolve.  If our car with its wheelbase
of 2.7 meters is traveling 45 meters per second (i.e. 100 miles per hour or 162 km/hour), then
60 milliseconds will elapse between the time a bump hits the front tire and the same bump hits 
the rear tire.  

In order to get good resolution, we want take at least ten samples between those two
events, so our sampling interval must be 6 milliseconds or 167 samples/second.

What about the lowest speed we can measure?  For the corrlation algorithm to work properly,
our circular buffer must be long enough to hold twice the number of samples between "front 
bump" and "rear bump".  If the lowest speed we're interested in is 2.5 meters/second (i.e. 
5.6 miles per hour or 9 km/hour), then 1.08 seconds will elapse between "front bump" and 
"rear bump".  With a sampling rate of 167 samples/second, then we need 2 * 167 * 2.7 / 2.5 
samples = 361 samples.

That's not huge, so we might as well splurge and round up to 512 samples (the nearest power 
of two) since this makes the circular buffer indeces easy to compute.  With a buffer that is
512 samples long, we can measure speeds as low as 1.76 meters / second (i.e. 3.94 miles/hour 
or 6.34 km/hour).

