#include"fileserve.h"
#include"libftp.h"
#include"Connection.h"
static char buffer[4096];
FileServer::FileServer(string path,int socket)
{
    this->socket = socket;
    this->currentPath = path;
    
}

void FileServer::HandleList()
{
    string path = this->currentPath;
    printf("Starting handle list Upload\n");
    vector<string> filePaths;
    char buffer[2048];
    DIR* dir;
    struct dirent *mdirent;
    dir = opendir(path.c_str());
    string prefix = (path == "."? "" : path+"/");
    string ans = "";
    while((mdirent = readdir(dir) ) != NULL)
    {
        string dname = string(mdirent -> d_name);
        string actualFile =prefix + dname;
        if(dname != "." && dname != "..")
            ans += actualFile + "\r";
            
    }
    ans += "\n";
    write(socket,ans.c_str(),ans.size());
    printf("List finished");

}


void FileServer::HandleUpload(string fileName,int psize)
{
    printf("Starting handle file Upload\n");

    ofstream file(fileName,ios::binary); 
    if(!file)
    {
        cout<< "failed loading files"<<endl;
        return ;
    }
    printf("openning file success\n");
    int readnum,packnum = 0;
    printf("client socket %d\n",socket);
    while(readnum = read(socket,buffer,4096))
    {
        file.write(buffer,readnum);
        packnum++;
        if(packnum == psize)
            break;
    }
    file.close();

}