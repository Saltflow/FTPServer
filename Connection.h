#ifndef CONN__HEADER
#define CONN__HEADER
#include<queue>
#include<vector>
#include <pthread.h>
#include <signal.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <unistd.h>
using std::queue;
using std::vector;

class Connection
{
    int sockNum;
    queue<int> workQueue;
    pthread_mutex_t wqMutex;
    pthread_cond_t wqCond;
    vector<pthread_t*> threadPool;

    void initThreadPool(int maxinum);


public:
    Connection(int maxinum,int listenPort);
    int Serve();

};


#endif