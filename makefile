CC=g++
flags=-std=c++0x -pthread
boost=-I /usr/local/boost_1_63_0


all:
	$(CC) $(flags) $(boost) main.cpp Bisem.cpp MessageQueue.cpp Consumer.cpp Logging.cpp Producer.cpp FlightInstrumentation.cpp -o fcmain

debug:
	$(CC) $(flags) $(boost) -g main.cpp Bisem.cpp MessageQueue.cpp Consumer.cpp Logging.cpp Producer.cpp FlightInstrumentation.cpp -o fc_debug

clean:
	rm fcmain fc_debug logfile.txt
