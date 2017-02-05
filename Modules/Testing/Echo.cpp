#include "Echo.h"
#include <iostream>
#include <cstring>
#include "../../Globals.h"


void Echo::run()
{

    datastruct data;
    while(true)
    {
        ready->get();

        pthread_mutex_lock(&datalock); 
        memcpy(&data, shared_mem, sizeof(struct datastruct));
        pthread_mutex_unlock(&datalock);

        std::cout << data.data1 << ", " << data.data2 << std::endl;

    } 

}

void Echo::stop()
{
    int a;
}
