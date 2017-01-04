//QueuedConsumer.cpp

#include <string>
#include "MessageQueue.h"
#include "Bisem.h"

QueuedConsumer::QueuedConsumer()
{
    msg_queue = new MessageQueue();
}

QueuedConsumer::~QueuedConsumer()
{
    delete msg_queue;
}

MessageQueue * QueuedConsumer::get_queue()
{
    return msg_queue;
}
