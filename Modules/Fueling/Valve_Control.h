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
       

        //APIs
        bool vent_tank();
        //
        //...


        list<Valve> get_valve_list();

        //api
        bool vopen(string valve_name);
        bool is_open(string valve_name);
        bool vclose(string valve_name);

    private:
        Valve_Parser parser;
        list<Valve> valve_list;

        //valve.h calls through valve_list
        bool actuate(string valve_name);
        bool is_actuated(string valve_name);


};


#endif
