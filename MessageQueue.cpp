//MessageQueue.cpp

#include "MessageQueue.h"
#include "Bisem.h"
#include <string>
#include <iostream>

//takes a bisem so we can post to it when things get pushed into the queue
MessageQueue::MessageQueue(Bisem * b) : b(b)
{
    pthread_mutex_init(&write_lock, NULL);
    qsize = 0;
}

MessageQueue::MessageQueue(const MessageQueue &other)
{
    std::cout << "MsgQueue copy ctor" << std::endl;
    pthread_mutex_init(&write_lock, NULL);
    b = other.b;
    qsize = 0;
}

MessageQueue & MessageQueue::operator= (const MessageQueue &other)
{
    b = other.b;
    pthread_mutex_init(&write_lock, NULL);
    qsize = 0;
    return *this;
}


MessageQueue::~MessageQueue()
{
    std::cout << "In MessageQueue dtor" << std::endl;
    /*
    * We store dynamically allocated strings in this queue (see push() for details)
    * so here we need to specially deallocate everything that is left in the queue;
    */
    std::string * temp;
    while( msg_queue.pop(temp) )
    {
        //std::cout << "Deleting : " << *temp << std::endl;
        delete temp;
        qsize--;
    }
    //std::cout << "done with MessageQueue dtor" << std::endl;
}

//blocking
//returns true on success
bool MessageQueue::push(Queued_Msg message)
{
    /*
    * boost::lockfree::queue requires things in it to have "trivial copy and assignment constructors"
    * which string doesnt have.
    * pointers do! so we dynamically allocate, copy, and push.
    * on dequeue we pop, copy, and deallocate.
    */
    std::string * temp = new std::string(message);
    
    pthread_mutex_lock(&write_lock);
    bool retval = msg_queue.unsynchronized_push(temp);
    pthread_mutex_unlock(&write_lock);

    qsize++;

    if(!retval) //if it didnt go in then delete it here.
    {
        qsize--;
        delete temp;
    }
    else
        b->post(); //if we succeeded then post to the bisem
    //dont worry, that string gets deleted later (in MessageQueue::pop()!)
    return retval;
}

//returns true on success.
//loads the message into $message
bool MessageQueue::pop(std::string &message)
{
    std::string * temp;
    bool retval = msg_queue.pop(temp);
    qsize--;
    if( !retval ) //if we failed
    {
        qsize++;
        return retval;
    }
    message = std::string(*temp);
    delete temp;
    return retval;
}

int MessageQueue::size()
{
    return qsize.load();
}
