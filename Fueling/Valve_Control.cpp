//Valve_Control.cpp


#include "Valve_Control.h"
#include "Valve.h"
#include <list>
#include <iterator>



using namespace std;

bool Valve_Control::actuate(string valve_name)
{
    for(list<Valve>::iterator it = valve_list.begin(); 
            it != valve_list.end();
            it++)
    {
        if( (*it).name() == valve_name )
        {
            return (*it).actuate();
        }
    }
    return false;
}

bool Valve_Control::is_actuated(string valve_name)
{
    for(list<Valve>::iterator it = valve_list.begin(); 
            it != valve_list.end();
            it++)
    {
        if( (*it).name() == valve_name )
        {
            return (*it).is_actuated();
        }
    }
    //todo: hmm...
    return false;
}



bool Valve_Control::vent_tank()
{
    actuate("valve_a");
    //time delays too
    actuate("valve_b");


}

