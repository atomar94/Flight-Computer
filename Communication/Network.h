//Network.h
//

#ifndef NETWORK_H
#define NETWORK_H

#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include "../MessageQueue.h"


using namespace std;

class Network
{
    public:
        Network();
        int nwrite(Queued_Msg msg);
        Queued_Msg nread();

    private:
        struct sockaddr_in ground_server;
        int ground_socket;



};

#endif
