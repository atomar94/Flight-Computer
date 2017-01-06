//Bisem.cpp

#include "Bisem.h"
#include <pthread.h>
#include <semaphore.h>

//init sem to 1
Bisem::Bisem() {
    sem_init(&counter, 0, 1); //init this to 1
}

//semaphores not copied
Bisem::Bisem(const Bisem &other)
{
    sem_init(&counter, 0, 1);
}

//semaphores are not copied
Bisem & Bisem::operator= (const Bisem &other)
{
   sem_init(&counter, 0, 1);
   return *this;
}

//sets the value of the sem to 1
void Bisem::post()
{
    int val;
    pthread_mutex_lock(&lock);
    sem_getvalue(&counter, &val);
    if(val == 0) {
        sem_post(&counter);
    }
    pthread_mutex_unlock(&lock);
}

//blocking
int Bisem::get()
{
    int temp = sem_wait(&counter);
    return temp;
}


