//main.cpp

#include "Logging.h"
#include "FlightInstrumentation.h"
#include "Globals.h"
#include "Consumer.h"
#include "MessageQueue.h"

#include <pthread.h>
#include <list>
#include <iostream>
#include <thread>

int main() {

    MessageQueue * m = new MessageQueue();
    m->push("Hello");
    m->push("World");
    delete m;
    return 0;


    //define all consumers
    Logging log = Logging();
    
    //put consumers in a list
    std::list<Consumer*> c;
    c.push_back( (Consumer*) &log);
    
    //define producers
    FlightInstrumentation flin = FlightInstrumentation(c);

    //start the consumers
    std::thread logthread(&Consumer::run, log);
    
    //start the producers
    std::thread flinthread(&Producer::run, flin);
    
    logthread.join();
    flinthread.join();
}
