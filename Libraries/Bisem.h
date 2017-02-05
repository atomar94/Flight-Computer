//Bisem.h

#include <semaphore.h>
#include <atomic>
#include <pthread.h>

#ifndef BISEM_H
#define BISEM_H

//bisem is a binary semaphore. the same as a normal semaphore
//but it only increments to 1. it is essentially a flag.
//

class Bisem
{
    private:
        pthread_mutex_t lock;
        sem_t counter;

    public:
        Bisem();
        Bisem(const Bisem &other);
        Bisem & operator= (const Bisem &other);

        void post();
        int get();

};

#endif
