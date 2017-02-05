//Producer.h

#include "../Globals.h"
#include "Consumer.h"
#include <list>
#include <string>
#include "MessageQueue.h"
#include <map>


#ifndef PRODUCER_H
#define PRODUCER_H


using namespace std;

class Producer
{

    public:
        Producer();
        virtual void run() = 0;
        virtual void stop();
        void help();

    protected:
        //functions
        virtual void get_sensors() = 0;
        void add_msg_queue_pair(string name, MessageQueue* mq);

        //variables
        datastruct sensor_data; //all our sensors go in this struct.
        std::list<Consumer*> consumers; //all the consumers from this producer.
        bool readyflag;
        map<string, MessageQueue*> message_queue_table;



};

#endif
