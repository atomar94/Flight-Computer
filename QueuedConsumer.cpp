//QueuedConsumer.cpp

#include <string>
#include "MessageQueue.h"
#include "QueuedConsumer.h"
#include "Bisem.h"
#include <iostream>

QueuedConsumer::QueuedConsumer()
{
    std::cout << "QueuedConsumer ctor" << std::endl;
    msg_queue = new MessageQueue(ready);
}


 
QueuedConsumer::QueuedConsumer(const QueuedConsumer &other)
{
    std::cout << "QueuedConsumer copy ctor" << std::endl;
    msg_queue = new MessageQueue(ready);

}

QueuedConsumer & QueuedConsumer::operator= (const QueuedConsumer &other)
{
    std::cout << "QueuedConsumer assignment operator" << std::endl;
    msg_queue = new MessageQueue(ready);
    return *this;
}


QueuedConsumer::~QueuedConsumer()
{
    std::cout << "QueuedConsumer dtor" << std::endl;
    delete msg_queue;
}

MessageQueue * QueuedConsumer::get_queue()
{
    return msg_queue;
}
