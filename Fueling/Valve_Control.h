//Valve_Control.h


#ifndef VALVE_CONTROL_H
#define VALVE_CONTROL_H

#include "Valve.h"
#include <list>

using namespace std;

class Valve_Control
{

    //todo: this needs to get populated somehow
    list<Valve> valve_list;

    //APIs
    bool vent_tank();
    //
    //...


    //valve.h calls through valve_list
    bool actuate(string valve_name);
    bool is_actuated(string valve_name);

};


#endif
