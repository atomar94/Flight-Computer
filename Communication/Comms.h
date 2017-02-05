//Comms.h
/*
 * Comms class reads what's in its message queue and sends
 * it to the correct communication medium. If we are using
 * the network then it formats an http request and sends
 * it accross the network. if its radio, we send it to the
 * radio.
 *
 * Anyone can add messages into the class and it will send
 * it.
 */

#include <list>
#include <string>

#include "Network.h"
#include "../Libraries/Bisem.h"
#include "../Libraries/MessageQueue.h"
#include "../Libraries/Producer.h"

#ifndef COMMS_H
#define COMMS_H

using namespace std;

class Comms : public Producer
{
    public:
        void run();
        void stop();

        Comms();
        ~Comms();
        MessageQueue * get_queue();
        void add_msg_queue(string name, MessageQueue *mq);

    private:
        MessageQueue * msg_queue; //outgoing (to network/radio) msgs
        Bisem * b; //needed for msg_queue but not actually used
        std::list<Queued_Msg> inbox; //incoming (from network) msgs
        Network command_server;
        bool runflag;        

        void get_network(); //load network recv into the inbox
        void get_radio(); //load radio recv into the inbox
        void dispatch(); //send the msgs in the inbox to their destinations.
        

};

#endif
