//Testing_Producer.h
//

#ifndef TESTING_PRODUCER_H
#define TESTING_PRODUCER_H

#include "../Fueling/Valve_Interface.h"
#include "../Logging.h"

class Testing_Producer : public Producer
{
    public:
        Testing_Producer();
        ~Testing_Producer();

        add_msg_queue_pair(); //todo: this could go in the producer class
        //overridden
        void run();
        void stop();

    private:
        //commands you can pass in
        void help();
        void set_data();
        void send_message();


        //simulation objects
        Valve_Interface * valves;
        Logging * logger;
};


#endif
