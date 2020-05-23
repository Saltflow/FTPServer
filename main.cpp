#include"Connection.h"
#include"database.h"
#include"libftp.h"
#include"fileserve.h"
void Login(int socket);
void Serv(int socket);
char buffer[2048];
void handleRequest(Connection * conn)
{
    while(true)
    {
        int socket = conn->getNext();
        Login(socket);
        Serv(socket);
    }   
}

int main(int argc,char **argv)
{
    
    Connection* conn = new Connection(10,21);
    conn->ServeFunction = handleRequest;
    conn->Start();
    return 0;
}

void Serv(int socket)
{
    FTPCommand cmd = FTPCommand(socket);
    FileDirectory RootDir = FileDirectory(".");
    while(true)
    {
        if(!cmd.Read())
        {
            printf("Clilent closed\n");
            return ;
        }
            
        string clientCmd = cmd.GetCommand();
        string cmdCont = cmd.GetAttrib();
        switch(clientCmd[0])
        {
            case 'R':
                break;

            case 'S':
                if(clientCmd == "SIZE")
                    break;
            case 'L':
                vector<string>* files = RootDir.List();
                string outList = string("212 ");
                for(unsigned i=0; i < files->size();i++)
                {
                    outList = outList + (*files)[i] + "\r";
                }
                outList = outList + "\n";
                cmd.SendResponse(outList);
                break;
        }
    }
}


void Login(int socket)
{
    FTPCommand login = FTPCommand(socket);
    login.Read();
    string usrCmd = login.GetCommand();
    if(usrCmd != string("USER"))
        login.SendResponse("404\n");
    string usrName = login.GetAttrib();
    printf("get Attribute of userName %s \n",usrName.c_str());
    if(!DataBase::GetInstance() -> checkUserNameOK(usrName))
        return ;
    login.SendResponse("331 password required\n");

    login.Read();
    usrCmd = login.GetCommand();
    if(usrCmd != string("PASS"))
        login.SendResponse("404\n");
    string userPass = login.GetAttrib();
    if(DataBase::GetInstance() -> checkPassWordOK(usrName,userPass))
    {
        printf("Validate Success\n");
        login.SendResponse("230 login success\n");
    }
}