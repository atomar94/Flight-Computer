//Ignition.cpp

#include "Ignition.h"
#include "Consumer.h"

//logging queue and radio queue
Ignition::Ignition(MessagaeQueue * l, MessageQueue * r) : Consumer(l, r)
{
}

//main loop
void Ignition::run()
{
    runflag = true;
    while(runflag) {
        ready->get(); //get ready semaphore

        // getlock, copy shared, unlock
        pthread_mutex_lock(&datalock); 
        memcpy(&data, shared_mem, sizeof(struct datastruct));
        pthread_mutex_unlock(&datalock);

        // if data says we should ignite...
        // boom()
        // if something important happened and should be logged (like igniton or abort)...
        // push_radio("Hey something cool just happened!")
        // push_log("Hey log this!")
   }
}

void Ignition::boom()
{
    //ignition code goes here
}
