//Network.cpp
//

#include <sys/socket.h> //socket types
#include <sys/types.h> // " "
#include <netinet/in.h> // " "
#include <stdio.h> //printf
#include <string> 
#include "Network.h"
#include <unistd.h> //read and write syscalls
#include <string.h> //memset
#include <arpa/inet.h>

using namespace std;

const char * GROUND_SERVER_IP = "192.168.0.1";
int GROUND_SERVER_PORT = 1919;

Network::Network()
{
    ground_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(ground_socket == 0)
    {
        printf("Error creating socket.\n");
    }
    memset(&ground_server, 0, sizeof(ground_server));
    ground_server.sin_family = AF_INET;

    inet_pton(AF_INET, GROUND_SERVER_IP, &ground_server.sin_addr);

    //ground_server.sin_addr.s_addr = GROUND_SERVER_IP;
    ground_server.sin_port = htons(GROUND_SERVER_PORT);

    if(connect(ground_socket, (struct sockaddr *) &ground_server, sizeof(ground_server)) < 0)
    {
        printf("Error connecting to Ground Server\n");
    }
}

int Network::nwrite(Queued_Msg msg)
{
    if(ground_socket > 0)
        return write(ground_socket, msg.payload.c_str(), 0);
    else
        return -1;

}

//we still need to parse the data we read and load it into the Queued_Msg
Queued_Msg Network::nread()
{
    Queued_Msg temp;
    if(ground_socket < 0)
        return temp;

    char buf[512];
    if(read(ground_socket, buf, 511) <= 0)
    {
        return temp;
    }
    else
    {
        //parse buf and load it into ret;
        Queued_Msg ret;
        ret.to = "Network::nread() not implemented yet";
        ret.dest = "Network::nread() not implemented yet";
        ret.payload = "Network::nread() not implemented yet";
        return ret;
    }
}





