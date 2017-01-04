//Consumer.h

#include "Bisem.h"
#include <pthread.h>
#include "Globals.h"

#ifndef CONSUMER_H
#define CONSUMER_H

class Consumer
{
    protected:
        Bisem * ready;
        pthread_mutex_t datalock;
        bool runflag = true;

        struct datastruct data; //local copy
        struct datastruct * shared_mem; //shared copy

    public:
        Consumer();
        ~Consumer();

        virtual void run() = 0; //run the consumer loop
        virtual void stop() = 0; //stop the consumer loop

        void notify(); //increments bisem

        //copies data from newdata to shared_mem.
        //returns true on update, else false.
        bool update_shared_memory(struct datastruct * newdata);
};

#endif
