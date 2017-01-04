//Communications.cpp



void Comms::run()
{
    runflag = true;
    while(runflag) {
        ready.get(); //get ready sem

        //if msg in queue send that

        //else send whats in the shared memory
        pthread_mutex_lock(&datalock);
        memcpy(&data, shared_mem, sizeof(struct datastruct));
        pthread_mutex_unlock(&datalock);






    }


}

void Comms::stop()
{
    runflag = false;
}
