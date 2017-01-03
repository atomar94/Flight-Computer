//logging.h

#include "Consumer.h"
#include "Globals.h"
#include <pthread.h>

#ifndef LOGGING_H
#define LOGGING_H

class Logging : public Consumer
{
    public:
        Logging(struct datastruct * shared_mem_loc);

        void run();
        void stop();

    private:
        int fp;
        pthread_mutex_t m;
};

#endif
