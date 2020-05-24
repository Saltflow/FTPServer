#include"fileserve.h"
#include"libftp.h"
#include"Connection.h"
static char buffer[4096];

FileDirectory::FileDirectory(string path)
{
    char buffer[2048];
    currentPath = path;
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



void FileDirectory::HandleUpload(string fileName)
{
    printf("Starting handle file Upload\n");
    Connection *fileConn = new Connection(1,20);
    printf("Connection success\n");
    ofstream file(fileName,ios::binary); 
    if(!file)
    {
        cout<< "failed loading files"<<endl;
        return ;
    }
    printf("openning file success\n");
    int clientSocket = fileConn->StartSingle();
    int readnum;
    printf("client socket %d\n");
    while(readnum = read(clientSocket,buffer,4096))
    {
        file.write(buffer,readnum);
    }
    file.close();
    delete(fileConn);

}