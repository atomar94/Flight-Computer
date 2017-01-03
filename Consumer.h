//Consumer.h

#include "Bisem.h"
#include <pthread.h>
#include "Globals.h"

#ifndef CONSUMER_H
#define CONSUMER_H

class Consumer
{
    protected:
        Bisem ready;
        pthread_mutex_t datalock;
        bool runflag = true;
        struct datastruct data;

        struct datastruct * shared_mem;

    public:
        Consumer(struct datastruct * shared_mem_loc);

        virtual void run() = 0; //run the consumer loop
        virtual void stop() = 0; //stop the consumer loop

        virtual bool trylock(); //returns true if lock acquired
        virtual void unlock();
        virtual void lock();
};

#endif
