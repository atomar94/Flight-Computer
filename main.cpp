//main.cpp

#include "Logging.h"
#include "Instrumentation.h"
#include "Globals.h"
#include "Consumer.h"
#include "MessageQueue.h"
#include "Echo.h"
#include "Fueling/Valve_Interface.h"


#include <pthread.h>
#include <list>
#include <iostream>
#include <thread>

void test_bisem()
{
    Bisem * b = new Bisem();
    MessageQueue * m = new MessageQueue(b);
    m->push("Hello");
    m->push("World");
    delete m;
    delete b;
}

void test_logging()
{

    //define all consumers
    Logging log = Logging();
    Echo e = Echo();


    //put consumers in a list
    std::list<Consumer*> c;
    c.push_back(&log);
    c.push_back(&e);

    //define producers
    Instrumentation flin = Instrumentation(c);


    //start the consumers
    // NOTE: THese threads must take a reference to the object.
    // if you pass a pointer or the object itself it will call the
    // copy constructor and then the queued messages and semaphores
    // will not be the same memory location and they wont work.

    std::cout << "spawning consumer thread" << std::endl;
    //std::thread logthread(&Consumer::run, &log);
    //std::thread echothread(&Consumer::run, &e);

    //start the producers
    std::cout << "spawning producer thread" << std::endl;
    //std::thread flinthread(&Producer::run, &flin);





}


void fuel_testing()
{

    Valve_Interface valves = Valve_Interface();




    //put consumers in a list
    std::list<Consumer*> c;
    c.push_back(&valves);


    //define producers
    Instrumentation flin = Instrumentation(c);


    //start the consumers
    // NOTE: THese threads must take a reference to the object.
    // if you pass a pointer or the object itself it will call the
    // copy constructor and then the queued messages and semaphores
    // will not be the same memory location and they wont work.

    std::cout << "spawning consumer thread" << std::endl;
    std::thread valve_control_thread( &Consumer::run, &valves);


    //start the producers
    std::cout << "spawning producer thread" << std::endl;
    //std::thread flinthread(&Producer::run, &flin);

    //echothread.join();
    //logthread.join();
    //flinthread.join();




}

int main() {

    //test_bisem();

    test_logging();

    


}
