//main.cpp

#include "Logging.h"
#include "FlightInstrumentation.h"
#include "Globals.h"
#include "Consumer.h"
#include "MessageQueue.h"
#include "Echo.h"

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
    FlightInstrumentation flin = FlightInstrumentation(c);


    //start the consumers
    // NOTE: THese threads must take a reference to the object.
    // if you pass a pointer or the object itself it will call the
    // copy constructor and then the queued messages and semaphores
    // will not be the same memory location and they wont work.

    std::cout << "spawning consumer thread" << std::endl;
    std::thread logthread(&Consumer::run, &log);
    std::thread echothread(&Consumer::run, &e);

    //start the producers
    std::cout << "spawning producer thread" << std::endl;
    std::thread flinthread(&Producer::run, &flin);

    echothread.join();
    logthread.join();
    flinthread.join();

}

class a
{
    public:
        int * ptr;
        a();
        ~a();
        void foo();
};

a::a()
{
    std::cout << "in ctor" << std::endl;
    ptr = new int();
}

a::~a()
{
    std::cout << "in dtor" << std::endl;
    delete ptr;
}

void a::foo()
{
    *ptr = 2;
}
int main() {

    //test_bisem();

    test_logging();

    


}
