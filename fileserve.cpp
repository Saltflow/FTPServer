#include"fileserve.h"
#include"libftp.h"
#include"Connection.h"
static char buffer[4096];
FileServer::FileServer(string path,int socket)
{
    this->socket = socket;
    char buffer[2048];
    DIR* dir;
    struct dirent *mdirent;
    dir = opendir(path.c_str());
    string prefix = (path == "."? "" : path+"/");
    while((mdirent = readdir(dir) ) != NULL)
    {
        string dname = string(mdirent -> d_name);
        string actualFile =prefix + dname;
        if(dname != "." && dname != "..")
            this->filePaths.push_back(actualFile);
    }
}



void FileServer::HandleUpload(string fileName)
{
    printf("Starting handle file Upload\n");

    printf("Connection success\n");
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
    }
    file.close();

}