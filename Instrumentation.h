//Instrumentation.h

#include "Producer.h"
#include "Drivers/MS5607_Driver.h"

#ifndef INSTRUMENTATION_H
#define INSTRUMENTATION_H
class Instrumentation : public Producer
{

    public:
        Instrumentation(std::list<Consumer*> &c);
        ~Instrumentation();
        void run();
    
    private:
        //hardware instances
        MS5607_Driver altimeter;

        void get_sensors();

};

#endif
