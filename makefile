all:
	g++ -std=c++0x -pthread main.cpp Bisem.cpp Consumer.cpp Logging.cpp -o fcmain

debug:
	g++ -std=c++0x -pthread -g main.cpp Bisem.cpp Consumer.cpp Logging.cpp -o fc_debug
