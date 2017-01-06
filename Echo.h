//Echo.h
//

#include "Consumer.h"

#ifndef ECHO_H
#define ECHO_H

class Echo : public Consumer
{
    public:
        void run();
        void stop();
};

#endif
