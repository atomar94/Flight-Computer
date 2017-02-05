//Instrumentation.cpp

#include <list>
#include <iostream>
#include <stdio.h>

#include "../Globals.h"
#include "../Libraries/Consumer.h"
#include "Instrumentation.h"

//ctor
Instrumentation::Instrumentation(std::list<Consumer*> &c) : Producer()
{
    std::cout << "Instrumentation ctor" << std::endl;
    consumers = std::list<Consumer*>(c);
    sensor_data.data1 = 0;
    sensor_data.data2 = 0;

    //initialize all hardware instances
    MS5607_Driver altimeter();
}

//dtor
Instrumentation::~Instrumentation()
{
 std::cout << "Instrumentation dtor" << std::endl;
}

// main producer loop
void Instrumentation::run()
{
    readyflag = true;
    while(true)
    {
        get_sensors();
        for( std::list<Consumer*>::iterator c = consumers.begin(); c != consumers.end(); ++c)
        {
            //if we are able to update shared mem...
            if( (*c)->update_shared_memory(&sensor_data) ) //c is a ptr to the list, and list has pointers, so double deref.
	        {
                    (*c)->notify(); //let the consumer know!
            }
	    }
    }
}


// Collects data from each of the sensors and loads it into the 
// sensor_data struct.
void Instrumentation::get_sensors()
{
    //keep now for testing
    sensor_data.data1++;
    sensor_data.data2++;


    sensor_data.pressure =    altimeter.pressure();
    sensor_data.temperature = altimeter.temperature();
    sensor_data.altitude =    altimeter.altitude();
}

