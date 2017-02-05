//valve parse main.cpp

#include "Valve_Parser.h"
#include <string>
#include <list>
#include <iostream>

using namespace std;

int main()
{
    Valve_Parser vp;
    vp.load_and_parse("valves.txt");
    list<Valve> valve_list = vp.get_valves();

    cout << "Final Valve List: " << endl;
 
    for(list<Valve>::iterator it = valve_list.begin();
            it != valve_list.end();
            it++)
    {
        cout << (*it).name() << "\t";
        if((*it).is_normal_open())
            cout << "open" << endl;
        else
            cout << "closed" << endl;

    }
}
