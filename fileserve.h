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

class FileDirectory
{
    vector<string> filePaths;
    string currentPath;

public:
    FileDirectory(string path);


    vector<string>* List()
    {
        return &this->filePaths;
    }

    

};

void OpenFileTransferSocket(string path);

#endif