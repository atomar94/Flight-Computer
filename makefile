CC=g++
flags=-std=c++0x -pthread
boost=-I /usr/local/boost_1_63_0

libraries=Libraries/Producer.cpp Libraries/Consumer.cpp Libraries/QueuedConsumer.cpp\
		  Libraries/MessageQueue.cpp Libraries/Bisem.cpp

logging=Modules/Logging/Logging.cpp
fueling=Modules/Fueling/Valve.cpp Modules/Fueling/Valve_Control.cpp \
		Modules/Fueling/Valve_Interface.cpp Modules/Fueling/Valve_Parser.cpp
testing=Modules/Testing/Echo.cpp
sim=Simulator/Testing_Producer.cpp

modules=$(logging) $(fueling) $(testing)

comms=Communication/Comms.cpp Communication/Network.cpp

#this target is for when we are on a vm that doesn't have the bcm Libraries
all:
	$(CC) $(flags) $(boost) main.cpp $(modules) $(sim) $(comms) $(libraries) -o fcmain


valve-parse:
	$(CC) $(flags) $(boost) valve_parse_main.cpp -C $(modules) $(sim) $(comms) $(libraries) -o vparse


#this target is for when we are on the pi and can compile the gpio Libraries
drivers:
	$(CC) $(flags) $(boost) main.cpp $(consumers) $(producers) $(helpers) $(fueling) $(simulator) $(comms) $(drivers) -o fcmain


debug:
	$(CC) $(flags) $(boost) -g main.cpp $(consumers) $(producers) $(helpers) $(fueling) $(simulator) $(drivers) -o fc_debug

clean:
	rm fcmain fc_debug logfile.txt
