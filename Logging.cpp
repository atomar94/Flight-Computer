//Logging.cpp
#include "Logging.h"
#include "QueuedConsumer.h"
#include "Globals.h"
#include <pthread.h>
#include "Bisem.h"
#include <cstring> //memcpy
#include <iostream> //cout
#include <fstream> //file stuff

Logging::Logging() : QueuedConsumer()
{
    std::cout << "Logging ctor" << std::endl;
}

Logging::~Logging()
{
    std::cout << "Logging dtor" << std::endl;
}

//main loop for this consumer
void Logging::run()
{
    //this must be allocated here because if we allocate in a different thread we have
    //very odd issues and segfaults.
    fp = new std::ofstream();
    fp->open("logfile.txt", std::ofstream::out);
    std::string message;

    runflag = true;
    while(runflag)
    {
        ready->get(); //get ready semaphore

        if(msg_queue->pop(message))
        {
            (*fp) << message << std::endl;
        } 
        else
        {
            // getlock, copy shared, unlock
            pthread_mutex_lock(&datalock); 
            memcpy(&data, shared_mem, sizeof(struct datastruct));
            pthread_mutex_unlock(&datalock);

            int a = 1;
            if( fp->good())
                a = 2;
            if( fp->fail())
                a = 3;
            (*fp) << data.data1 << ", " << data.data2 << std::endl;
        }
        if(msg_queue->size() > 0) //if there are more things in the queue
        {
           notify();
        }
    }
    fp->close();
    delete fp;
}

//set runflag false so the run loop stops()
void Logging::stop()
{
    runflag = false;
}
