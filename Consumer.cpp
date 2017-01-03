//Consumer.cpp

#include "Consumer.h"
#include "Globals.h"

Consumer::Consumer(struct datastruct * shared_mem_loc)
{
    shared_mem = shared_mem_loc;
    ready = Bisem();
    pthread_mutex_init(&datalock, NULL);
}


//Returns true if the lock was acquired, else false
bool Consumer::trylock() {
    if(!pthread_mutex_trylock(&datalock))
        return true;
    return false;
}

void Consumer::unlock() {
    pthread_mutex_unlock(&datalock);
}

void Consumer::lock() {
    pthread_mutex_lock(&datalock);
}

//declared but unused because if it was pure virtual then our
//member variables would not instantiate and datalock (forexample)
//would block everytime.
//
//that was a gnarley bug to track down.
void Consumer::run()
{

}

void Consumer::stop()
{

}
