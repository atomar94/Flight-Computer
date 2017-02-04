//Valve_Interface.cpp


#include "Valve_Interface.h"
#include <string>

void Valve_Interface::run()
{
    runflag = true;
    while(runflag)
    {

        string message; 
        if( msg_queue->pop(message) )
        {
            //parse message
            v_control.actuate("what did the msg say?");
        }


    }



}

void Valve_Interface::stop()
{
    runflag = false;
}
