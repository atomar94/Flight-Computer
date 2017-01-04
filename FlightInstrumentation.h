//FlightInstrumentation.h

#include "Producer.h"

#ifndef FLIGHTINSTRUMENTATION_H
#define FLIGHTINSTRUMENTATION_H
class FlightInstrumentation : public Producer
{

    public:
        FlightInstrumentation(std::list<Consumer*> &c);
        ~FlightInstrumentation();
        void run();
    
    private:
        void get_sensors();

};

#endif
