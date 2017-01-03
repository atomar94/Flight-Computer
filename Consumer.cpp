//Consumer.cpp

#include "Consumer.h"
#include "Globals.h"
#include "string.h"

Consumer::Consumer()
{
    shared_mem = new datastruct;
    ready = Bisem();
    pthread_mutex_init(&datalock, NULL);
}

void Consumer::notify() {
    ready.post();
}

//Copies the data from newdata to the location of shared_mem.
//returns true if it updated and false otherwise.
bool Consumer::update_shared_memory(struct datastruct * newdata)
{
    if( ! pthread_mutex_trylock(&datalock) ) {
        memcpy(shared_mem, newdata, sizeof(struct datastruct));
        pthread_mutex_unlock(&datalock);
        return true;
    }
    return false;
}




