//Valve_Control.h

/*
 * Valve_Control is the controller for all valves.
 * High level "macro" operations can be defined here.
 *
 * This involkes the Valve_Parser to read in valves.txt
 * and create a bunch of valve objects
 */

#ifndef VALVE_CONTROL_H
#define VALVE_CONTROL_H

#include "Valve.h"
#include <list>
#include "Valve_Parser.h"

using namespace std;

class Valve_Control
{

    public:
        Valve_Control();
        //todo: this needs to get populated somehow
        list<Valve> valve_list;
        

        //APIs
        bool vent_tank();
        //
        //...


        //valve.h calls through valve_list
        bool actuate(string valve_name);
        bool is_actuated(string valve_name);

    private:
        Valve_Parser parser;
};


#endif
