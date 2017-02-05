#Modules/Fueling/makefile

CC=g++
flags=-std=c++0x -pthread
boost=-I /usr/local/boost_1_63_0

files=Logging.cpp

all:
	$(CC) $(flags) $(boost) $(files)


