//Testing_Producer.cpp
//

#include "Testing_Producer.h"
#include <string>
#include <sstream>
#include <iostream>
#include <list>
#include <unistd.h> //sleep and usleep
#include "../Fueling/Valve_Interface.h"
#include "../Logging.h"
#include "../Globals.h"
#include "../Libraries/Producer.h"
#include "../Libraries/Consumer.h"


using namespace std;


//ctor
Testing_Producer::Testing_Producer(list<Consumer*> &c) : Producer()
{
    consumers = std::list<Consumer*>(c);
}

Testing_Producer::~Testing_Producer()
{
}

void Testing_Producer::add_msg_queue(string name, MessageQueue* mq)
{
    add_msg_queue_pair(name, mq);
}

void Testing_Producer::run()
{
    string input;
    readyflag = true;
    while(readyflag)
    {
        //start parsing
        cout << endl << ">";
        getline(cin, input);
        if(debug)
            cout << "got input: " << input << endl;
        list<string> tok = split(input, ' ');
        if(debug)
        {
            cout << "Parsed args: " << endl;
            for(list<string>::iterator it = tok.begin();
                    it != tok.end();
                    it++)
            {
                cout << "\t" << *it << endl;
            }

        } 

        //route commands
        string root_cmd = tok.front();
        
        if(root_cmd == "help")
            help();

        else if(root_cmd == "set-data")
            set_data(tok);

        else if(root_cmd == "send-message")
            send_message(tok);

        else if(root_cmd == "debug")
            set_debug(tok);

        else if(root_cmd == "gen-data")
            gen_data(tok);

        else if(root_cmd == "tick")
            tick(tok); //wake up in the morning feelin' like P diddy

        else
            cout << "cmd " << root_cmd << " not found" << endl;

        //main loop
        for(int i = 0; i < run_counter; i++)
        {
            if(debug)
            {
                cout << "in main loop " << i << " of "; 
                cout << run_counter << endl;
            }
            get_sensors();
            for( list<Consumer*>::iterator c = consumers.begin(); 
                    c != consumers.end(); 
                    ++c)
             {
                //if we are able to update shared mem...
                if( (*c)->update_shared_memory(&sensor_data) )
	            {
                    (*c)->notify(); //let the consumer know!
                }
	        }
            usleep(100*1000); //100 ms
        }
        run_counter = 0;

    } //end main loop
}

//this should probably call the simulator program
void Testing_Producer::get_sensors()
{
    return;
}

//cmd line args below

//help
void Testing_Producer::help()
{

    cout << "Testing Mode - Help" << endl;
    cout << "Commands" << endl;

    //help
    cout << "help" << endl;
    cout << "\t\t print help information" << endl;

    //debug
    cout << "debug <true/false>" << endl;
    cout << "\t\t true to put the simulator in debug mode. false for silence." << endl;


    //tick
    cout << "tick *<num>" << endl;
    cout << "\t\t Have the computer do <num> iterations" << endl;
    cout << "\t\t without stopping to read cmds." << endl;
    cout << "\t\t if <num> is not supplied it defaults to 1" << endl;


    //set-data
    cout << "set-data <data-field> <value>" << endl;
    cout << "\t\t set the data for <data-field> that is sent to the shared mem for each consumer." << endl;
    cout << "\t\t these datafields are available:" << endl;
    cout << "\t\t 'pressure', 'temperature', 'altitude'";
    cout << ", 'gyrox', 'gyroy', 'gyroz', 'accelx', 'accely'";
    cout << ".'accelz'" << endl;
    cout << endl;


    //gen-data
    cout << "gen-data <generator> *<arg>" << endl;
    cout << "\t\t have the computer generate data for the sensor values." << endl;
    cout << "\t\t The following generators are supported:" << endl;
    cout << "\t\t gen-data flat *<value>" << endl;
    cout << "\t\t\t all data is set to <value>. If value is not supplied it defaults to 1.234" << endl;
    cout << endl; 


    //send-message
    cout << "send-message <dest> <message>" << endl;
    cout << "\t\t send a message via the msg queues." << endl;
    cout << "\t\t these dests are available:" << endl;
    cout << "\t\t 'fueling', 'logging''" << endl;
    cout << "\t\t message should be surrounded in quotes" << endl;
    cout << "\t\t example: send-message fueling \"my message\"" << endl;
    cout << " *** *** ***" << endl;
}

void Testing_Producer::gen_data(list<string> cmd)
{
    list<string> temp = cmd;
    string first = temp.front();
    temp.pop_front();
    string second = temp.front();
    temp.pop_front();

    if(first != "gen-data")
        return;

    if(second == "flat")
        flat_data(cmd);
}

//debug
void Testing_Producer::set_debug(list<string> cmd)
{
    string first = cmd.front();
    cmd.pop_front();
    string val = cmd.front();
    if(first != "debug")
        return;
    else if(val == "true")
    {
        debug = true;
        cout << "Simulator set debug mode." << endl;
    }
    else if(val == "false")
    {
        debug = false;
        cout << "Simulator set to silent mode." << endl;
    }
    else
    {
        cout << "Couldn't read value: " << val << endl;
        cout << "this must be 'true' or 'false' (no quotes)" << endl;
    }

}

void Testing_Producer::tick(list<string> cmd)
{
    string first = cmd.front();
    cmd.pop_front();

    int times = 1;
    if(cmd.size() > 0)
        times = stoi(cmd.front());

    if(debug)
        cout << "setting run_counter to " << times << endl;
    run_counter = times; 

}

void Testing_Producer::stop()
{
    readyflag = false;
}

//set-data <data-field> <value>
//
//use this to set the value of a datafield that gets passed to the consumers
void Testing_Producer::set_data(list<string> cmd)
{
    string first;
    string second;
    string third;
    try {
        first = cmd.front();
        cmd.pop_front();
        second = cmd.front();
        cmd.pop_front();
        third = cmd.front();
        cmd.pop_front();
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
        sensor_data.temperature = val;

    else if(second == "altitude")
        sensor_data.altitude = val;

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
    if(debug)
    {
        cout << "send-message called with args" << endl;
        for(list<string>::iterator it = cmd.begin();
                it != cmd.end();
                it++)
        {
            cout << "\t" << *it << endl;
        }

    }
    string first = cmd.front();
    cmd.pop_front();
    if(debug)
        cout << "cmd parsed: " << first << endl;
    string dest = cmd.front();
    cmd.pop_front();
    if(debug)
        cout << "dest parsed: " << dest << endl;

    //find matching message queue for this destination.
    map<string, MessageQueue*>::iterator mq;
    mq = message_queue_table.find(dest);
    if (mq == message_queue_table.end())
    {
        cout << "Could not find dest: " << dest << endl;
        return;
    }
    else if(debug)
        cout << "Found dest" << endl;

    string message = "";
    bool message_flag = false;
    int i = 0;
    
    //form message string from tokenized input
    for(list<string>::iterator it = cmd.begin();
            it != cmd.end();
            it++, i++)
    {

        if( (*it).front() == '"')
        {
            message_flag = true; //msg has started
            message.append( (*it).substr(1, (*it).size() - 1) + " ");
            continue;
        }

        if( (* (*it).end()) == '"')
        {
            message_flag = false;
            message.append( (*it).substr(0, (*it).size() - 2) + " ");

            break;
            //this break stops the parse, so all metadata is ignored
            //fix this if we want metadata
        }

        if(message_flag)
        {
            message.append( *it );
        }
    }//end for token in cmd_string
    
    if(debug)
        cout << "Sending " << message << " to " << dest << endl;

    Queued_Msg out;
    out.to = dest;
    out.dest = "needs to be implemented";
    out.payload = message;

    ((*mq).second)->push(out); 

}

//simulation program
//all data is set to a constant value
void Testing_Producer::flat_data(list<string> cmd)
{
    string first = cmd.front();
    cmd.pop_front();
    string second = cmd.front();
    cmd.pop_front();

    float val = 1.234; //default
    if( cmd.size() > 0)
    {
        val = stof(cmd.front());
    }

    sensor_data.pressure = val;
    sensor_data.temperature = val;
    sensor_data.altitude = val;
    sensor_data.gyro.x = val;
    sensor_data.gyro.y = val;
    sensor_data.gyro.z = val;
    sensor_data.accel.x = val;
    sensor_data.accel.y = val;
    sensor_data.accel.x = val;


}

list<string> Testing_Producer::split(string str, char delim)
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
 

                   
