//Valve_Interface.h
//


/*
 *
 *This class is the interface between the Valve_Control class
 * and the multithreaded 
 *
 *
 * This consumer doesn't look at it's shared memory, it just
 * loops and reads log queue messages.
 *
 */
#ifndef VALVE_INTERFACE_H
#define VALVE_INTERFACE_H

#include "../QueuedConsumer.h"
#include "Valve_Control.h"

class Valve_Interface : public QueuedConsumer
{

    public:
        

        //overridden from Comsumer
        void run();
        void stop();

    private:
        Valve_Control v_control;
};

#endif
