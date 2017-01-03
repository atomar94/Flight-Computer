//logging.h

#include "Consumer.h"
#include "Globals.h"
#include <pthread.h>

#ifndef LOGGING_H
#define LOGGING_H

class Logging : public Consumer
{
    public:
        Logging();

        void run();
        void stop();

    private:
        int fp;
};

#endif
