//Comms.cpp

#include "Network.h"
#include "Comms.h"
#include "../Libraries/MessageQueue.h"
#include <iostream>

using namespace std;

Comms::Comms()
{
    //command_server();

    b = new Bisem(); //not used in this instance, but still required.
    msg_queue = new MessageQueue(b);
    runflag = true;
}

Comms::~Comms()
{
    delete msg_queue;
    delete b;
}

void Comms::add_msg_queue(string name, MessageQueue* mq)
{
    add_msg_queue_pair(name, mq);
}

void Comms::run()
{
    runflag = true;
    Queued_Msg outbound;

    while(runflag)
    {
        //get latest
        get_network();
        get_radio();

        //handle the network and radio requests
        dispatch();


        //write all the inbox msgs in the queue
        int size = msg_queue->size();
        for(int _ = 0; _ < size; _++)
        {
            if(msg_queue->pop(outbound))
            {
                //if outbound is for network
                if(outbound.to == "network")
                    command_server.nwrite(outbound);
                //if(outbound.to == "radio")
                    //radio.nwrite()
            }
        }
    }
}

void Comms::stop()
{
    runflag = false;
}


//load the contents of the network socket
//into the inbox
void Comms::get_network()
{
    Queued_Msg q_msg;
    q_msg = command_server.nread();
    if( q_msg.to != "invalid" )
    {
        inbox.push_back(q_msg);
    }
}


//todo implement
//
//This gets the data from the radio 
void Comms::get_radio()
{
    return;
}

//a message came in via wireless and we need to send it
//to whatever class controls that functionality
//
//This needs to read the metadata for the inbox objects
// and decide which message queue to send it to.
//
void Comms::dispatch()
{
    int size = inbox.size();
    Queued_Msg outbound;
    map<string, MessageQueue*>::iterator mq;

    for(int _ = 0; _ < size; _++)
    {
        outbound = inbox.front();
        inbox.pop_front();

        //find matching message queue for this Queued_Msg.
        mq = message_queue_table.find( outbound.to );
        if (mq != message_queue_table.end())
        {
            ((*mq).second)->push(outbound);
        }
        else
        {
            cout << "couldn't find: " << outbound.to << " for payload<";
            cout << outbound.payload << "> it was dropped." <<endl;
        }

   }
}



