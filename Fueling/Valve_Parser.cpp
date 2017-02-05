//Valve_Parser.cpp

#include "Valve_Parser.h"
#include "Valve.h"
#include <string>
#include <list>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

void Valve_Parser::load_and_parse(string filename)
{
    cout << "Starting Parser" << endl;
    ifstream ifs(filename.c_str());

    string line;
    string token;
    string valve_name = "";
    bool valve_normal_open;


    for(int line_number = 0; 
            getline(ifs, line);
            line_number++)
    {
        if(debug)
            cout << "on line " << line_number << endl;

        if(line.front() == '#')
            continue;
        if(line.size() == 0)
            continue;

        valve_name = "";
        valve_normal_open = false;

        //for word in line
        stringstream line_stream(line);
        for(int word_number = 0;
                getline(line_stream, token, ' ');
                word_number++)
        {
            if(debug)
                cout << "\ton word " << word_number << endl;
            if(token == "")
            {
                cout << "Hey there's some weird shit on line " << line_number << endl;
                break;
            }

            if(word_number == 0)
            {
                if(debug)
                    cout << "\t\tgot valve name " << token << endl;
                valve_name = token;
            }
            else if(word_number == 1)
            {
               if(token == "open")
                   valve_normal_open = true;

               else if(token == "closed")
                   valve_normal_open = false;

               else
               {
                   cout << "Didn't find correct 'normal'";
                   cout << "field on line " << line_number;
                   cout << " valid values are open and closed";
                   cout << endl;
                   break;
               }
               valves.push_back(Valve(valve_name, valve_normal_open)); 
               break;
            }
            else //word_number > 1
            {
                  break;
            }
       } //end for word...
    } //end for line...


}

list<Valve> Valve_Parser::get_valves()
{
    return valves;
}
