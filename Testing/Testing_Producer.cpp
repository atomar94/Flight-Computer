//Testing_Producer.cpp
//

#include "Testing_Producer.h"
#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <pair>
#include "../Fueling/Valve_Interface.h"
#include "../Logging.h"

using namespace std;


//ctor
Testing_Producer::Testing_Producer() : Producer()
{
    //create all objects for this simulation
    valves = new Valve_Interface();
    logger = new Logging();

    consumers = std::list<Consumer*>();
    consumers.push_back(valves);
    consumers.push_back(logger);

    add_msg_queue_pair("fueling", valves.get_queue());
}

Testing_Producer::~Testing_Producer()
{
    delete valves;
    delete logger;
}


void Testing_Producer::run()
{
    string input;
    while(true)
    {
        cin >> input;
        list<string> tok = split(input, ' ');
        
        string root_cmd = tok.front();
        
        if(root_cmd == "help")
        {
            help();
        }

    }
}


void Testing_Producer::help()
{

    cout << "Testing Mode - Help" << endl;
    cout << "Commands" << endl;

    //help
    cout << "help\t\t\tprint help information" << endl;
    cout << endl;

    //set-data
    cout << "set-data <data-field> <value>" << endl;
    cout << "\t\t set the data for <data-field> that is sent to the shared mem for each consumer." << endl;
    cout << "\t\t these datafields are available:" << endl;
    cout << "\t\t 'pressure', 'temperature', 'altitude'";
    cout << ", 'gyrox', 'gyroy', 'gyroz', 'accelx', 'accely'";
    cout << ".'accelz'" << endl;
    cout << endl;

    //send-message
    cout << "send-message <dest> <message> <metadata>*" << endl;
    cout << "\t\t send a message via the msg queues. metadata is optional." << end;
    cout << "\t\t these dests are available:" << endl;
    cout << "\t\t 'fueling', 'logging''" << endl;
    cout << "\t\t message should be surrounded in quotes" << endl;
    cout << "\t\t example: send-message fueling \"my message\"" << endl;
    cout << " *** *** ***" << endl;
}

void Testing_Producer::set_data(list<string> cmd)
{
    try {
        string first = cmd.pop_front();
        string second =  cmd.pop_front();
        string third = cmd.pop_front();
    } 
    catch(const exception e)
    {
        cout << "Invalid syntax.";
        cout << " Usage: set-data <data-field> <value>" << endl;
        return;
    }


    float val = stof(third);


    if(first != "set-data")
        return;
    
    if(second == "pressure")
        sensor_data.pressure = val;

    else if(second == "temperature")
        sensor_data.pressure = val;

    else if(second == "altitude")
        sensor_data.pressure = val;

    else if(second == "gyrox")
        sensor_data.gyro.x = val;

    else if(second == "gyroy")
        sensor_data.gyro.y = val;

    else if(second == "gyroz")
        sensor_data.gyro.z = val;

    else if(second == "accelx")
        sensor_data.accel.x = val;

    else if(second == "accely")
        sensor_data.accel.y = val;

    else if(second == "accelz")
        sensor_data.accel.x = val;

    else
    {
        cout << "Could not find data field " << second << endl;
    }
}

//send-message <to> <message> <metadata>*
void Testing_Producer::send_message(list<string> cmd)
{
    string message = "";
    bool message_flag = false;

    for(list<string>::iterator it = cmd.begin();
            it != cmd.end();
            it++)
    {
        if(it == cmd.begin() && it != "send-message")
            return;


        if((*it).front() == '"')
        {
            message_flag = true; //msg has started
            message.append( (*it).substr(1, (*it).size() - 1) );
            continue;
        }

        if((*it).end() == '"')
        {
            message_flag = false;
            message.append( (*it).substr(0, (*it).size() - 1));

            break;
            //this break stops the parse, so all metadata is ignored
            //fix this if we want metadata
        }

        if(message_flag)
        {
            message.append( *it );
        }
    }


}

list<string> split(string str, char delim)
{
    stringstream ss;
    ss.str(str);
    string token;
    list<string> l;
    while(getline(ss, token, delim))
    {
        l.push_back(token);
    }
    return l;
}
 

                   
