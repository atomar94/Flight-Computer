//MessageQueue.cpp

#include "MessageQueue.h"
#include <string>
#include <iostream>

MessageQueue::MessageQueue()
{
    pthread_mutex_init(&write_lock, NULL);
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
        std::cout << "Deleting : " << *temp << std::endl;
        delete temp;
    }
}

//blocking
//returns true on success
bool MessageQueue::push(std::string message)
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
    
    if(!retval) //if it didnt go in then delete it here.
    {
        delete temp;
    }
    return retval;
}

//returns true on success.
//loads the message into $message
bool MessageQueue::pop(std::string &message)
{
    std::string * temp;
    bool retval = msg_queue.pop(temp);
    if( !retval )
    {
        return retval;
    }
    message = std::string(*temp);
    delete temp;
    return retval;
}
