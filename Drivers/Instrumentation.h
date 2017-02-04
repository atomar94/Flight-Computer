//Instrumentation.h


/*
 *  Main Data acquisition loop for the flight computer
 *
 *  this is going to loop through all the instruments and
 *  collect the data
 *
 *
 */

#include "../Producer.h"
#include "MS5607_Driver.h"

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
