//QueuedConsumer.h

#include "MessageQueue.h"
#include "Consumer.h"

#ifndef QUEUEDCONSUMER_H
#define QUEUEDCONSUMER_H

class QueuedConsumer : public Consumer
{
    public:
        QueuedConsumer();
        QueuedConsumer(const QueuedConsumer &other);
        QueuedConsumer & operator= (const QueuedConsumer &other);
        ~QueuedConsumer();
        MessageQueue * get_queue();
    
    protected:
        MessageQueue * msg_queue;


};

#endif
