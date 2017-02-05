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
        Valve(string name, bool norm_open);
        bool is_actuated(); 
        bool actuate();
        string name();
        bool is_normal_open();

    private:
        bool normal_open;
        string metadata;
        string m_name;


};


#endif
