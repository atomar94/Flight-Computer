//Producer.cpp

#include "Producer.h"

//ctor
Producer::Producer()
{
    readyflag = false;
}

void Producer::stop()
{
    readyflag = false;
}
