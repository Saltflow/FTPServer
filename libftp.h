#ifndef __libftp__serv__
#define __libftp__serv__
#include<string>
#include<iostream>
#include"Connection.h"
#include<sstream>
using namespace std;
const int buffsize = 1024;

class FTPCommand{
    string command;
    string attrib;
    int sockNum;
    char buffer[buffsize];

    public:
        FTPCommand(int socket);

        string GetCommand();

        void Read();

        string GetAttrib();

        void SendResponse(string command);

};



#endif