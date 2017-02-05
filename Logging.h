//logging.h

#include "Libraries/QueuedConsumer.h"
#include "Globals.h"
#include <pthread.h>
#include <fstream> //output to file
#include <iostream> //also file

#ifndef LOGGING_H
#define LOGGING_H

class Logging : public QueuedConsumer
{
    public:
        Logging();
        ~Logging();

        bool open_file();

        void run();
        void stop();

    private:
        std::ofstream * fp; //ofstream has no copy constructor so we assign with ptrs.
};

#endif
