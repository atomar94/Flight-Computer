//MessageQueue.h

#include "boost/lockfree/queue.hpp"
#include <pthread.h>
#include <string>

#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

//threadsafe mutlireader multiwriter dynamically allocating queue.
class MessageQueue
{
    public:
        MessageQueue();
        //TODO this needs a copy constructor, otherwise we need to dynamically allocate every instance.
        ~MessageQueue();
        bool push(std::string message);
        bool pop(std::string &message);

    private:
        pthread_mutex_t write_lock;
        boost::lockfree::queue<std::string*> msg_queue{32}; //start with 32 prealloc'ed nodes


};

#endif
