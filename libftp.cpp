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

void FTPCommand::SendResponse(int code)
{
    string ans;
    switch(code)
    {
        case 200:
            ans = "200 success\n";
            break;
        case 230:
            ans = "230 login success\n";
            break;
        case 331:
            ans = "331 password required\n";
            break;
        case 404:
            ans = "404 error\n";
            break;
    }
    dprintf(sockNum,"%s",ans.c_str());
}