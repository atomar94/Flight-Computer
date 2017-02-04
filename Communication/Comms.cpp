//Comms.cpp

#include "Network.h"
#include "Comms.h"
#include "../MessageQueue.h"

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

void Comms::start()
{
    runflag = true;
    Queued_Msg outbound;

    while(runflag)
    {
        //get latest
        get_network();
        get_radio();
        
        //write all the msgs in the queue
        int size = msg_queue->size();
        for(int _ = 0; _ < size; _++)
        {
            if(msg_queue->pop(outbound))
            {
                //if outbound is for network
                command_server.nwrite(outbound);
                //if outbound is for radio
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

//a message came in and we need to send it
//to whatever class controls that functionality
//
//
//This needs to read the metadata for the inbox objects
// and decide which message queue to send it to.
//
void Comms::dispatch()
{
    int size = inbox.size();
    for(int _ = 0; _ < size; _++)
    {
        /*
         * if msg.is_for(fueling)
         *   send_to_fueling_queue(msg)
         * else if msg.is_for(ignition)
         *   send_to_ignition_queue(msg)
         */
    }
}



