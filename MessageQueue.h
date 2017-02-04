//MessageQueue.h

#include "boost/lockfree/queue.hpp"
#include <pthread.h>
#include <string>
#include <atomic>

#include "Bisem.h"

#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

//message structure

using namespace std;

struct Queued_Msg
{
    string * to; //what object
    string * dest; //where its going (eventually)
    string * payload; //information we want to send

};

//threadsafe mutlireader multiwriter dynamically allocating queue.
//Note this class has no copy constructor and some member variabled dont have copy constructors so
//unless we define our own we can't use copy assignment.
// AKA this must be assigned via dynamic instantiation
// AKA MessageQueue * m = new MessageQueue();
class MessageQueue
{
    public:
        MessageQueue(Bisem * b);
        MessageQueue(const MessageQueue &other);
        MessageQueue & operator= (const MessageQueue &other);
        ~MessageQueue();

        bool push(Queued_Message message);
        bool pop(Queued_Message &message);
        int size();

    private:
        pthread_mutex_t write_lock;
        boost::lockfree::queue<Queued_Msg*> msg_queue{32}; //start with 32 prealloc'ed nodes
        std::atomic<int> qsize;
        Bisem * b;


};

#endif
