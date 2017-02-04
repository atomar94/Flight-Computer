//Logging.cpp
#include "Logging.h"
#include "QueuedConsumer.h"
#include "Globals.h"
#include "Bisem.h"

#include <pthread.h> //mutex
#include <sys/stat.h> //check if file exists
#include <cstring> //memcpy
#include <iostream> //cout
#include <fstream> //file stuff


using namespace std;

Logging::Logging() : QueuedConsumer()
{
    std::cout << "Logging ctor" << std::endl;
    fp = new std::ofstream();
    open_file();
}

Logging::~Logging()
{
    std::cout << "Logging dtor" << std::endl;
    delete fp;
}

//main loop for this consumer
void Logging::run()
{
    std::string message;

    runflag = true;
    while(runflag)
    {
        ready->get(); //get ready semaphore

        if(msg_queue->pop(message))
        {
            (*fp) << message << std::endl;
        } 
        else
        {
            // getlock, copy shared, unlock
            pthread_mutex_lock(&datalock); 
            memcpy(&data, shared_mem, sizeof(struct datastruct));
            pthread_mutex_unlock(&datalock);

            int a = 1;
            if( fp->good())
                a = 2;
            if( fp->fail())
                a = 3;
            (*fp) << data.data1 << ", " << data.data2 << std::endl;
        }
        if(msg_queue->size() > 0) //if there are more things in the queue
        {
           notify();
        }
    }
    fp->close();
    delete fp;
}

//set runflag false so the run loop stops()
void Logging::stop()
{
    runflag = false;
}

//finds a filename thatis not taken and opens it.
//returns true on success else false
bool Logging::open_file()
{
    string filename_formatter_str = "./Logs/log%d.txt";
    const char * filename_formatter = filename_formatter_str.c_str();
    char filename[16];
    int i = 0;

    struct stat buf;
    do
    {
        sprintf(filename, filename_formatter, i);
        i++;
    }
    while(stat(filename, &buf) != -1); //while this filename already exists...

    fp->open(filename, std::ofstream::out);
}
