//Valve.h

#ifndef VALVE_H
#define VALVE_H

/*
 *TODO: Implement Valve class.
 *
 *This class should actuate the gpio pins to interact with hardware
 * and control a single valve.
 */

#include <string>

using namespace std;

class Valve
{
    public:
        bool is_actuated(); 
        bool actuate();
        string name();
        string metadata;
        string m_name;
};


#endif
