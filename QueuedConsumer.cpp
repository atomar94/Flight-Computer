//QueuedConsumer.cpp

#include <string>
#include "MessageQueue.h"
#include "QueuedConsumer.h"
#include "Bisem.h"

QueuedConsumer::QueuedConsumer()
{
    msg_queue = new MessageQueue(ready);
}

QueuedConsumer::~QueuedConsumer()
{
    delete msg_queue;
}

MessageQueue * QueuedConsumer::get_queue()
{
    return msg_queue;
}
