CC=g++
flags=-std=c++0x -pthread
boost=-I /usr/local/boost_1_63_0
consumers=Consumer.cpp QueuedConsumer.cpp Logging.cpp Ignition/Ignition.cpp Echo.cpp
producers=Producer.cpp
helpers=Bisem.cpp MessageQueue.cpp
fueling=Fueling/Valve.cpp Fueling/Valve_Control.cpp Fueling/Valve_Interface.cpp
simulator=Simulator/Testing_Producer.cpp
drivers=Drivers/MS5607_Driver.cpp Drivers/Instrumentation.cpp
comms=Communication/Comms.cpp Communication/Network.cpp

#this target is for when we are on a vm that doesn't have the bcm libraries
all:
	$(CC) $(flags) $(boost) main.cpp $(consumers) $(producers) $(helpers) $(fueling) $(simulator) $(comms) -o fcmain

#this target is for when we are on the pi and can compile the gpio libraries
drivers:
	$(CC) $(flags) $(boost) main.cpp $(consumers) $(producers) $(helpers) $(fueling) $(simulator) $(drivers) -o fcmain



debug:
	$(CC) $(flags) $(boost) -g main.cpp $(consumers) $(producers) $(helpers) $(fueling) $(simulator) $(drivers) -o fc_debug

clean:
	rm fcmain fc_debug logfile.txt
