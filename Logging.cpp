//Logging.cpp
#include "Logging.h"
#include "Globals.h"
#include <pthread.h>
#include <cstring> //memcpy
#include <stdio.h> //printf
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

Logging::Logging(struct datastruct * shared_mem_loc) : Consumer(shared_mem_loc)
{
    fp = open("logfile.txt", O_WRONLY | O_CREAT);
}

void Logging::run()
{
    runflag = true;
    while(runflag) {
        ready.get(); //get ready semaphore

        // getlock, copy shared, unlock
        pthread_mutex_lock(&datalock); 
        memcpy(&data, shared_mem, sizeof(struct datastruct));
        pthread_mutex_unlock(&datalock);
        write(fp, "hi", 2);
        break;
        //printf("%d, %d", data.data1, data.data2);
    }
}

//set runflag false so the run loop stops()
void Logging::stop()
{
    runflag = false;
}
