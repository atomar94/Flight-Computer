#include <atomic>
#include <pthread.h>

class Consumer()
{
    private:
        std::atomic<bool> ready = False;
        pthread_mutex_t datalock;
        bool runflag = True;

    public:
        Consumer();

        virtual void run() = 0; //run the consumer loop
        virtual void stop() = 0; //stop the consumer loop

}
