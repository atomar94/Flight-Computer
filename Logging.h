//logging.h

#include "QueuedConsumer.h"
#include "Globals.h"
#include <pthread.h>

#ifndef LOGGING_H
#define LOGGING_H

class Logging : public QueuedConsumer
{
    public:
        Logging();

        void run();
        void stop();

    private:
        int fp;
};

#endif
