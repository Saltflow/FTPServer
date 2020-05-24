#include"libftp.h"


FTPCommand::FTPCommand(int socket)
{
        this->sockNum = socket;
}

bool FTPCommand::Read()
{
    int readnum = read(sockNum,buffer,buffsize);
    if(readnum == 0)
    {
        printf("socket closed!\n");
        return false;
    }
    buffer[readnum] = '\0';
    stringstream sstr(buffer);
    sstr >> command >> attrib;
    cout <<"get command " << command << " with attribute " << attrib << endl;
    return true;
}

string FTPCommand::GetCommand()
{
    return this->command;
}

string FTPCommand::GetAttrib()
{
    return this->attrib;
}

void FTPCommand::SendResponse(string command)
{
    dprintf(sockNum,"%s",command.c_str());
}