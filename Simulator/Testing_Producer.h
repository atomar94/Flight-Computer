//Testing_Producer.h
//

#ifndef TESTING_PRODUCER_H
#define TESTING_PRODUCER_H

#include "../Fueling/Valve_Interface.h"
#include "../Logging.h"
#include "../Libraries/Producer.h"
#include <list>
#include <string>
#include "../Libraries/Consumer.h"

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

        //FC control commands
        void help();
        void set_debug(list<string> cmd);
        void set_data(list<string> cmd);
        void send_message(list<string> cmd);

        //simulator control commands
        void tick(list<string> cmd);

        //simulation programs
        void gen_data(list<string> cmd);
        void flat_data(list<string> cmd);

        //simulator internal variables
        int run_counter; //how many times we should iterate the FC

        //helper functions
        list<string> split(string std, char delim);

        //more verbose output
        bool debug = false;

};


#endif
