# Flight-Computer
This is the flight computer for a supersonic, liquid-propellant rocket. The rocket was designed and built by students at UCLA. The flight computer is in charge of the fueling process, ignition, control systems, and telemetry for the rocket. It is written in C++ and runs on three Raspberry Pis.

# Overview

Internally, the flight computer uses a single producer, multi-consumer model. The Producer is responsible for gathering the instrumentation data, such as heading, altitude, and fuel pressure, and giving it to each of the subsystems, or Consumers, to operate on. For example, the Producer gathers data and gives it to the Controls Consumer, a subsystem responsible for controlling our engine shutdown to ensure we reach our target altitude. The Controls Consumer reads in the data given to it by the Producer and runs the control algorithm on it to determine whether or not it should begin shutting down the engine.

![System Architecture](https://i.imgur.com/aTOdGDo.png)

## Concurrency

The flight computer is fully parallel and thread-safe, meaning the Producer and all Consumers run simultaneously. This allows us to have fast Consumers, like the Controls Consumer, run alongside a slower Consumer, like the Logging Consumer, without a performance hit. When the Producer gathers data and writes it into a Consumer's shared memory it notifies the Consumer that there is "fresh data" to work with. The Consumer either wakes up and either A) reads in the data and begins working, or B) is in the middle of working with previous data and ignores it. A fast Consumer might finish it's job quickly and have to wait until the flight computer notifies it that there is new data while a slow Consumer might be notified of fresh data 3 or 4 times (and thus miss 3 or 4 packets) while it is still working with an older data set.

### Message Queues

Most of the time it's okay if the Consumers miss a data update. As long as they are operating on the newest readings then there is no problem. But sometimes we have information that *must* be operated, such as notifying the Communication system that we've begun ignition sequence. This is too important to just get overwritten by the Producer so instead we can put it into a Message Queue. Some Consumers, like Logging and Communications, have Message Queues associated with them. The Producer, and any Consumer, can write into the Messaging Queue and be sure that information is operated on.

Consumers with Messaging Queues are called "Queued Consumers". They are functionally identical except that they will receive notifications when their queue is written to and they will always empty their queue before operating on fresh data. Because reading the queue means more chances for data from the Producer to be missed the Message Queues are only used for important, not-frequent updated.
