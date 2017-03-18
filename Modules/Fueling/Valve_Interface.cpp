//Valve_Interface.cpp


#include "Valve_Interface.h"
#include <string>
#include "../../Libraries/MessageQueue.h"
#include <sstream>

void Valve_Interface::run()
{
    runflag = true;
    while(runflag)
    {

        Queued_Msg message; 
        if( msg_queue->pop(message) )
        {
            if(message.to != "fueling")
            {
                if(debug)
                {
                    cout << "Fueling got to: " << message.to << endl;
                    cout << "dest: " << message.dest << endl;
                    cout << "Payload: " << message.payload << endl;
                    cout << "this pkt was dropped." << endl; 
                }
                continue;
            }
            //parse message
            if(message.payload == "get-all")
            {
                if(debug)
                    cout << "Fueling received get-all cmd" << endl;
                

            }
            v_control.actuate("what did the msg say?");
        }


    }



}

void Valve_Interface::stop()
{
    runflag = false;
}

//get all the valves under this interface
string Valve_Interface::get_all()
{
    stringstream ret;

    list<Valve> vl = v_control.get_valve_list();
    for(list<Valve>::iterator it = vl.begin();
            it != vl.end();
            it++)
    {
        ret << (*it).name() << " ";

        if( (*it).is_normal_open())
        {
            ret << "open" << endl;
        }
        else
            ret << "closed" << endl;
    }
    return ret.str();
}

bool Valve_Interface::is_open(string valve_name)
{
    
}

bool Valve_Interface::open(string valve_name)
{

}


