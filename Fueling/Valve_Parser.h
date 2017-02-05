//Valve_Parser.h

#ifndef VALVE_PARSER_H
#define VALVE_PARSER_H

#include <string>
#include <list>
#include "Valve.h"

using namespace std;

class Valve_Parser
{
    public:
        void load_and_parse(string filename);
        list<Valve> get_valves();       

    private:
        list<Valve> valves;
        bool debug = false;
};




#endif
