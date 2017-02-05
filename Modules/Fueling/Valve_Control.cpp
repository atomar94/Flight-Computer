//Valve_Control.cpp


#include "Valve_Control.h"
#include "Valve.h"
#include <list>
#include <iterator>
#include "Valve_Parser.h"


using namespace std;


Valve_Control::Valve_Control()
{

    parser.load_and_parse("valves.txt");
    valve_list = parser.get_valves();
}

//loop through the valves we have and if the name
//matches then actuate that one
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

