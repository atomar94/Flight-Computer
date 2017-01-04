//Producer.h

#include "Globals.h"
#include "Consumer.h"
#include <list>


#ifndef PRODUCER_H
#define PRODUCER_H

class Producer
{

    public:
        Producer();
        virtual void run() = 0;
        virtual void stop();

    protected:
        //functions
        virtual void get_sensors() = 0;

        //variables
        datastruct sensor_data; //all our sensors go in this struct. sloppy. fix later.
        std::list<Consumer*> consumers; //all the consumers from this producer.
        bool readyflag;
        



};

#endif
