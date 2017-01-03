//Logging.cpp
#include "Logging.h"
#include "Globals.h"
#include <pthread.h>
#include <cstring> //memcpy
#include <stdio.h> //printf
#include <iostream>
#include <unistd.h>
#include <fcntl.h>

Logging::Logging() : Consumer()
{
    fp = open("logfile.txt", O_WRONLY | O_CREAT);
}

//main loop for this consumer
void Logging::run()
{
    runflag = true;
    while(runflag) {
        ready.get(); //get ready semaphore

        // getlock, copy shared, unlock
        pthread_mutex_lock(&datalock); 
        memcpy(&data, shared_mem, sizeof(struct datastruct));
        pthread_mutex_unlock(&datalock);

        char databuf[32];
        sprintf(databuf, "%d, %d", data.data1, data.data2);
        write(fp, databuf, strlen(databuf));
   }
}

//set runflag false so the run loop stops()
void Logging::stop()
{
    runflag = false;
}
