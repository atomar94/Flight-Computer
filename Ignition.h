//Ignition.h

#include "Consumer.h"
#include "MessageQueue.h"

/*
* This class is an example of a Consumer class.
* 
* Ignition code is subject to change (and definitely will!) but this
* is a good template to see consumer behavior.
*/


#ifndef IGNITION_H
#define IGNITION_H

class Ignition : public Consumer
{
    public:
        Ignition(MessageQueue * r, MessageQueue * l);
        
        void run();
        void boom();
};


#endif
