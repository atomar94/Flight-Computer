//QueuedConsumer.h

#include "MessageQueue.h"

#ifndef QUEUEDCONSUMER_H
#define QUEUEDCONSUMER_H

class QueuedConsumer : public Consumer
{
    public:
        QueuedConsumer();
        ~QueuedConsumer();
        MessageQueue * get_queue();
    
    private:
        MessageQueue * msg_queue;


};

#endif
