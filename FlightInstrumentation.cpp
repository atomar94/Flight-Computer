//FlightInstrumentation.cpp

#include <list>
#include "Globals.h"
#include "Consumer.h"
//FlightInstrumentation.cpp

#include "FlightInstrumentation.h"
#include <stdio.h>

//ctor
FlightInstrumentation::FlightInstrumentation(std::list<Consumer*> &c) : Producer()
{
    printf("inside flin ctor\n");
    consumers = new std::list<Consumer*>(c);
    printf("Size of list is %d\n", consumers->size());

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
    printf("Size of list is %d\n", consumers->size());
    for( std::list<Consumer*>::iterator c = consumers->begin(); c != consumers->end(); ++c)
    {
        printf("Inside producer iteration loop\n");
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

