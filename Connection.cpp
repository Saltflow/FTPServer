
#include"Connection.h"

Connection::Connection(int maxinum,int listenPort)
{
    int status;
    int *socketNumber = new int;
    *socketNumber = socket(AF_INET,SOCK_STREAM,0);

    int socket_option = 1;
    if (setsockopt(*socketNumber, SOL_SOCKET, SO_REUSEADDR, &socket_option,
        sizeof(socket_option)) == -1) 
    {
        perror("Failed to set socket options");
        exit(errno);
    }

    struct sockaddr_in serv_address;
    memset(&serv_address,0,sizeof(serv_address));
    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons(listenPort);
    serv_address.sin_addr.s_addr = INADDR_ANY;

    status = bind(*socketNumber, (struct sockaddr *) &serv_address,sizeof(serv_address));
    if(status == -1)
        perror("bind failed\n");
    status = listen(*socketNumber, 50);
    if(status == -1)
        perror("listen failed\n");

    this->sockNum = *socketNumber;
    this->maxNum = maxinum;
    
}

void Connection::Start()
{
    initThreadPool(maxNum);
    printf("Thead Pool init\n");
    while (1) 
    {
        int client_socket = accept(sockNum, NULL, NULL);
        printf("Accept client\n");
        if(client_socket < 0) 
        {
            perror("Failed to accept connection\n");
            continue;
        }
        printf("pushing to work_queue\n");
        pthread_mutex_lock(&wqMutex);
        workQueue.push(client_socket);
        pthread_cond_signal(&wqCond);
        pthread_mutex_unlock(&wqMutex);
  }
}



void Connection::initThreadPool(int maxinum)
{
    pthread_mutex_init(&wqMutex,NULL);
    pthread_cond_init(&wqCond,NULL);
    for(int i=0;i<maxinum;i++)
    {
        thread* newThread = new thread(ServeFunction,this);  
        threadPool.push_back(newThread); 
    }
   
}

int Connection::getNext()
{
    int clientSocket;
    printf("Getting Next\n");
    pthread_mutex_lock(&wqMutex);
    while(workQueue.size() == 0)
    {
        pthread_cond_wait(&wqCond,&wqMutex);
    }
    printf("Get Next Finished\n");
    clientSocket = workQueue.front();
    workQueue.pop();
    pthread_mutex_unlock(&wqMutex);
    return clientSocket;
}
