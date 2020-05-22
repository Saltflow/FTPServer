#include"Connection.h"

char buffer[2048];
void handleRequest(Connection * conn)
{
    int socket = conn->getNext();
    printf("Hello, this is a thread! %d\n",socket);
    read(socket,buffer,1000);
    printf("buffer content :%s",buffer);
    write(socket,buffer,1000);
}

int main(int argc,char **argv)
{
    Connection* conn = new Connection(10,21);
    conn->ServeFunction = handleRequest;
    conn->Start();
    return 0;
}