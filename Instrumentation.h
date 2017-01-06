//Instrumentation.h

#include "Producer.h"

#ifndef INSTRUMENTATION_H
#define INSTRUMENTATION_H
class Instrumentation : public Producer
{

    public:
        Instrumentation(std::list<Consumer*> &c);
        ~Instrumentation();
        void run();
    
    private:
        void get_sensors();

};

#endif
