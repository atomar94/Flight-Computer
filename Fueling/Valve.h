//Valve.h

#ifndef VALVE_H
#define VALVE_H

/*
 *TODO: Implement Valve class.
 *
 *This class should actuate the gpio pins to interact with hardware
 * and control a single valve.
 */

class Valve
{
    public:
        bool is_actuated(); 
        bool actuate(string valve_name);
        string name;
        string metadata;
}


#endif
