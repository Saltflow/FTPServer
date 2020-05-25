#include"main.h"

char buffer[2048];
void handleRequest(Connection * conn)
{
    while(true)
    {
        int socket = conn->getNext();
        if(Login(socket))
        {
            Serv(socket);
        }
    }   
}

int main(int argc,char **argv)
{
    
    Connection* conn = new Connection(10,21);
    conn->ServeFunction = handleRequest;
    conn->Start();
    return 0;
}

void Serv(int cmdSocket)
{
    FTPCommand cmd = FTPCommand(cmdSocket);
    //PASV
    cmd.Read();
    int dataSocket;
    int dataPort = Connection::getFreeDataPort(&dataSocket);

    char dataPort_s[256];
    sprintf(dataPort_s,"%d\n",dataPort);
    cmd.SendResponse(string("227 Entering PASV mode ")+ string(dataPort_s));

    dataSocket = Connection::StartSingle(dataSocket);
    printf("data connection finished with dataSocket\n");


    FileServer RootDir = FileServer(".",dataSocket);
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
                if(clientCmd == "STOR")
                {
                    RootDir.HandleUpload(cmdCont);
                    printf("Upload success!\n");
                    cmd.SendResponse("200 success");
                    break;
                }
            case 'L':
                printf("Listing");
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


bool Login(int socket)
{
    //looping until we get a correct UserID and password

    FTPCommand login = FTPCommand(socket);
    login.Read();
    string usrCmd = login.GetCommand();
    if(usrCmd != string("USER"))
        login.SendResponse("404\n");
    string usrName = login.GetAttrib();
    printf("get Attribute of userName %s \n",usrName.c_str());
    if(!DataBase::GetInstance() -> checkUserNameOK(usrName))
        return false;
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
        return true;
    }
    return false;
}