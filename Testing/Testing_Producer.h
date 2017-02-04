//Testing_Producer.h
//

#ifndef TESTING_PRODUCER_H
#define TESTING_PRODUCER_H

#include "../Fueling/Valve_Interface.h"
#include "../Logging.h"
#include "../Producer.h"
#include <list>
#include <string>

using namespace std;

class Testing_Producer : public Producer
{
    public:
        Testing_Producer();
        ~Testing_Producer();

        //overridden
        void run();

    private:
        //commands you can pass in
        void help();
        void set_data(list<string> cmd);
        void send_message(list<string> cmd);

        //simulation objects
        Valve_Interface * valves;
        Logging * logger;

        //helper functions
        list<string> split(string std, char delim);



};


#endif
