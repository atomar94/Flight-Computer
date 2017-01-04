//Logging.cpp
#include "Logging.h"
#include "QueuedConsumer.h"
#include "Globals.h"
#include <pthread.h>
#include "Bisem.h"
#include <cstring> //memcpy
#include <stdio.h> //printf
#include <iostream> //cout
#include <unistd.h>
#include <fcntl.h>

Logging::Logging() : QueuedConsumer()
{
    fp = open("logfile.txt", O_WRONLY | O_CREAT);
}

//main loop for this consumer
void Logging::run()
{
    std::string message;
    runflag = true;
    while(runflag) {
        ready->get(); //get ready semaphore

        if(msg_queue->pop(message))
        {
            write(fp, message, message.length());
        }
        else
        {
            // getlock, copy shared, unlock
            pthread_mutex_lock(&datalock); 
            memcpy(&data, shared_mem, sizeof(struct datastruct));
            pthread_mutex_unlock(&datalock);

            char databuf[32];
            sprintf(databuf, "%d, %d", data.data1, data.data2);
            write(fp, databuf, strlen(databuf));
        }
        if(msg_queue->size() > 0) //if there are more things in the queue
        {
            notify();
        }
   }
}

//set runflag false so the run loop stops()
void Logging::stop()
{
    runflag = false;
}
