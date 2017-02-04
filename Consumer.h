//Consumer.h

#include "Bisem.h"
#include <pthread.h>
#include "Globals.h"
#include "MessageQueue.h"

#ifndef CONSUMER_H
#define CONSUMER_H

class Consumer
{
    protected:
        Bisem * ready;
        pthread_mutex_t datalock;
        bool runflag = true;
        MessageQueue * radio_queue;
        MessageQueue * log_queue;

        struct datastruct data; //local copy
        struct datastruct * shared_mem; //shared copy

    public:
        Consumer(MessageQueue * l=nullptr, MessageQueue * r=nullptr);
        Consumer(const Consumer &other);
        Consumer & operator= (const Consumer &other);

        ~Consumer();

        virtual void run() = 0; //run the consumer loop
        virtual void stop() = 0; //stop the consumer loop

        void notify(); //increments bisem

        void help();

        //copies data from newdata to shared_mem.
        //returns true on update, else false.
        bool update_shared_memory(struct datastruct * newdata);

        void push_radio(Queued_Msg msg); //push string to radio queue
        void push_log(Queued_Msg msg); //push string to logging queue
};

#endif
