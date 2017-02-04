CC=g++
flags=-std=c++0x -pthread
boost=-I /usr/local/boost_1_63_0
consumers=Consumer.cpp QueuedConsumer.cpp Logging.cpp Ignition.cpp Echo.cpp
producers=Producer.cpp Instrumentation.cpp
helpers=Bisem.cpp MessageQueue.cpp
comms=Communication/Comms.cpp Communication/Network.cpp

all:
	$(CC) $(flags) $(boost) main.cpp $(consumers) $(producers) $(helpers) $(comms) -o fcmain

debug:
	$(CC) $(flags) $(boost) -g main.cpp $(consumers) $(producers) $(helpers) $(comms) -o fc_debug

clean:
	rm fcmain fc_debug logfile.txt
