//Comms.h

#include "Consumer.h"
#include <list>
#include <string>

#ifndef COMMS_H
#define COMMS_H

class Comms : Consumer
{
    public:
        void run();
        void stop();

        Comms(std::list<string> msg_ll);

    private:
        std::list<string> msg_queue; 
}








#endif
