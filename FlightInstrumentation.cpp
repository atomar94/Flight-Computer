//FlightInstrumentation.cpp

#include <list>
#include "Globals.h"
#include "Consumer.h"
//FlightInstrumentation.cpp

#include "FlightInstrumentation.h"


//ctor
FlightInstrumentation::FlightInstrumentation(std::list<Consumer*> &c) : Producer()
{
    consumers = new std::list<Consumer*>(c);
}

//dtor
FlightInstrumentation::~FlightInstrumentation()
{
    delete consumers;
}

// main producer loop
void FlightInstrumentation::run()
{
    get_sensors();
    
    for( std::list<Consumer*>::iterator c = consumers->begin(); c != consumers->end(); c++)
    {
        //if we are able to update shared mem...
        if( (*c)->update_shared_memory(&sensor_data) ) //c is a ptr to the list, and list has pointers, so double deref.
        {
            (*c)->notify(); //let the consumer know!
        }
    
    }

}


// Collects data from each of the sensors and loads it into the 
// sensor_data struct.
void FlightInstrumentation::get_sensors()
{
    sensor_data.data1 = 4;
    sensor_data.data2 = 5;
}

