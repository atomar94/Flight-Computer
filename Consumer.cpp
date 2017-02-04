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

//copy ctor
Consumer::Consumer(const Consumer &other)
{
    std::cout << "Consumer copy ctor" << std::endl;
    shared_mem = new datastruct;
    *shared_mem = *other.shared_mem;

    ready = new Bisem();

    pthread_mutex_init(&datalock, NULL);

}

Consumer & Consumer::operator= (const Consumer &other)
{
    std::cout << "Consumer Assignment operator" << std::endl;

    if(this == &other)
        return *this;

    *shared_mem = *other.shared_mem;

    return *this;
}

Consumer::~Consumer()
{
    std::cout << "Consumer dtor" << std::endl;
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
void Consumer::push_radio(Queued_Msg msg)
{
    if(radio_queue)
    {
        radio_queue->push(msg);
    }
}

//if a valid log_queue was supplied then push into it
void Consumer::push_log(Queued_Msg msg)
{
    if(log_queue)
    {
        log_queue->push(msg);
    }
}

void Consumer::help()
{
    std::cout << "Bisem Loc: " << ready << std::endl;
}
