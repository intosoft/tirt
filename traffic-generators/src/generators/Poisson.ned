package traffic_generators.generators;

//
// Generates messages with a configurable interarrival time.
//
simple Poisson extends Source
{
    parameters:
        sendInterval @unit(s) = default(poisson(10)*1s);
}
