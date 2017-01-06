//Producer.cpp

#include "Producer.h"
#include <iostream>
#include <list>


//ctor
Producer::Producer()
{
    readyflag = false;
}

void Producer::stop()
{
    readyflag = false;
}

void Producer::help()
{
    std::cout << "Producer help" << std::endl;
    for( std::list<Consumer*>::iterator c = consumers.begin(); c != consumers.end(); ++c)
    {
        (*c)->help();
    }
}
