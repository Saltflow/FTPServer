#ifndef SOCKET__HEADER
#define SOCKET__HEADER

#include <sys/socket.h>
#include <unistd.h>

class Socket{

    bool isServer;

public:
    Socket();
    void* request_handler(void *);

    void Serve(int server_port);

    
}

#endif