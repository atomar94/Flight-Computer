#Modules/Fueling/makefile

CC=g++
flags=-std=c++0x -pthread
boost=-I /usr/local/boost_1_63_0

fueling=Valve.cpp Valve_Control.cpp Valve_Interface.cpp Valve_Parser.cpp

all:
	$(CC) $(flags) $(boost) $(fueling)


