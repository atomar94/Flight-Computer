#include <semaphore.h>
#include <atomic>
#include <pthread.h>
//bisem is a binary semaphore. the same as a normal semaphore
//but it only increments to 1. it is essentially a flag.
//

class Bisem
{
    private:
        sem_t counter;
        pthread_mutex_t lock;

    public:
        bool post();
        int get();
        bool tryget();
        Bisem();
};
