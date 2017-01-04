//MessageQueue.h

#include "boost/lockfree/queue.hpp"
#include <pthread.h>
#include <string>
#include <atomic>

#include "Bisem.h"

#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

//threadsafe mutlireader multiwriter dynamically allocating queue.
//Note this class has no copy constructor and some member variabled dont have copy constructors so
//unless we define our own we can't use copy assignment.
// AKA this must be assigned via dynamic instantiation
// AKA MessageQueue * m = new MessageQueue();
class MessageQueue
{
    public:
        MessageQueue(Bisem * b);
        //TODO this needs a copy constructor, otherwise we need to dynamically allocate every instance.
        ~MessageQueue();
        bool push(std::string message);
        bool pop(std::string &message);
        int size();

    private:
        pthread_mutex_t write_lock;
        boost::lockfree::queue<std::string*> msg_queue{32}; //start with 32 prealloc'ed nodes
        std::atomic<int> qsize;
        Bisem * b;


};

#endif
