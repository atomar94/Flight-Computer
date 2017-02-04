//Testing_Producer.h
//

#ifndef TESTING_PRODUCER_H
#define TESTING_PRODUCER_H

#include "../Fueling/Valve_Interface.h"
#include "../Logging.h"
#include "../Producer.h"
#include <list>
#include <string>
#include "../Consumer.h"

using namespace std;

class Testing_Producer : public Producer
{
    public:
        Testing_Producer(list<Consumer*> &c);
        ~Testing_Producer();

        //overridden
        void run();
        void stop();
        void add_msg_queue(string name, MessageQueue*);

    private:
        void get_sensors();

        //commands you can pass in
        void help();
        void set_data(list<string> cmd);
        void send_message(list<string> cmd);

        //simulation objects
        Valve_Interface * valves;
        Logging * logger;

        //helper functions
        list<string> split(string std, char delim);

        //more verbose output
        bool debug = true;

};


#endif
