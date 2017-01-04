//Consumer.cpp

#include "Consumer.h"
#include "Globals.h"
#include "string.h"
#include "Bisem.h"

#include <iostream>

Consumer::Consumer(MessageQueue * l, MessageQueue * r)
{
    log_queue = l;
    radio_queue = r;

    shared_mem = new datastruct;
    ready = new Bisem(); //this must be dynamically allocated or else there is a semaphore mismatch when we spawn a new thread.
    pthread_mutex_init(&datalock, NULL);
}


Consumer::~Consumer()
{
    delete shared_mem;
    delete ready;
}

//increment the semaphore so this consumer knows it has more data to read
void Consumer::notify() {
    ready->post();
}


//Copies the data from newdata to the location of shared_mem.
//returns true if it updated and false otherwise.
bool Consumer::update_shared_memory(struct datastruct * newdata)
{
    if( ! pthread_mutex_trylock(&datalock) ) {
        memcpy(shared_mem, newdata, sizeof(struct datastruct));
        pthread_mutex_unlock(&datalock);
        return true;
    }
    return false;
}

//if a valid radio_queue was supplied then push into it
void Consumer::push_radio(std::string msg)
{
    if(radio_queue)
    {
        radio_queue->push(msg);
    }
}

//if a valid log_queue was supplied then push into it
void Consumer::push_log(std::string msg)
{
    if(log_queue)
    {
        log_queue->push(msg);
    }
}


