#ifndef __file_serv__
#define __file_serv__

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;


class FileServer
{
    int socket;
    string currentPath;
    string usrName;

public:
    FileServer(string path,int socket);

    void HandleUpload(string fileName,int psize);
    void HandleDownload(string fileName);
    void HandleList();
    void HandleSize(string fileName);
    bool HandleCWD(string Directory);


    

};



#endif