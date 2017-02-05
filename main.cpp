//main.cpp

#include "Modules/Logging/Logging.h"

//#include "Instrumentation.h"

#include "Globals.h"
#include "Libraries/Consumer.h"
#include "Libraries/MessageQueue.h"
#include "Modules/Testing/Echo.h"
#include "Modules/Fueling/Valve_Interface.h"
#include "Simulator/Testing_Producer.h"

#include <pthread.h>
#include <list>
#include <iostream>
#include <thread>

void test_bisem()
{
    Bisem * b = new Bisem();
    MessageQueue * m = new MessageQueue(b);
    //m->push("Hello");
    //m->push("World");
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
    //commented out because this doesnt compile without rpi hardware
    //Instrumentation flin = Instrumentation(c);


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

//simulator
void fuel_testing()
{

    //construct simulation objects
    Valve_Interface valves = Valve_Interface();
    Logging logging = Logging();

    //put consumers in a list
    std::list<Consumer*> c;
    c.push_back(&valves);
    c.push_back(&logging);

    //Construct simulation
    Testing_Producer sim = Testing_Producer(c);

    //register message queues with the simulator
    sim.add_msg_queue("logging", logging.get_queue());
    sim.add_msg_queue("fueling", valves.get_queue());

    //start the consumers
    // NOTE: THese threads must take a reference to the object.
    // if you pass a pointer or the object itself it will call the
    // copy constructor and then the queued messages and semaphores
    // will not be the same memory location and they wont work.
    std::thread valve_control_thread( &Consumer::run, &valves);
    std::thread logging_thread( &Consumer::run, &logging);

    //start the simulator
    std::thread sim_thread(&Producer::run, &sim);

    valve_control_thread.join();
    logging_thread.join();
    sim_thread.join();

}

int main() {

    //test_bisem();

    //test_logging();

    fuel_testing();


}
