//Bisem.cpp

#include "Bisem.h"
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

//init sem to 1
Bisem::Bisem() {
    sem_init(&counter, 0, 1); //init this to 1
}

//sets the value of the sem to 1
void Bisem::post()
{
    int val;
    pthread_mutex_lock(&lock);
    std::cout << "post on sem@ " << &counter << " bisem instance@ " << this << std::endl;
    sem_getvalue(&counter, &val);
    if(val == 0) {
        
        sem_post(&counter);
    }
    pthread_mutex_unlock(&lock);
}

//blocking
int Bisem::get()
{
    std::cout << "waiting on sem@ " << &counter << " Bisem instance@ " << this << std::endl;
    int temp = sem_wait(&counter);
    std::cout << "Got sem!" << std::endl;
    return temp;
}


