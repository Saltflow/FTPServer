#ifndef SOCKET__HEADER
#define SOCKET__HEADER

#include <sys/socket.h>
#include <unistd.h>

class Socket{
    int sockNum;
    bool isServer;

public:
    Socket();

    void Serve(int server_port);

    
}

#endif