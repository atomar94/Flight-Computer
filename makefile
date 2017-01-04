CC=g++
flags=-std=c++0x -pthread


all:
	$(CC) $(flags) main.cpp Bisem.cpp Consumer.cpp Logging.cpp Producer.cpp FlightInstrumentation.cpp -o fcmain

debug:
	g++ -std=c++0x -pthread -g main.cpp Bisem.cpp Consumer.cpp Logging.cpp -o fc_debug
