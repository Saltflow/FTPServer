#include"fileserve.h"
#include"libftp.h"
#include"Connection.h"

FileDirectory::FileDirectory(string path)
{
    char buffer[2048];
    currentPath = path;
    DIR* dir;
    struct dirent *mdirent;
    dir = opendir(path.c_str());
    char* offset = buffer;
    string prefix = (path == "."? "" : path+"/");
    while((mdirent = readdir(dir) ) != NULL)
    {
        string dname = string(mdirent -> d_name);
        string actualFile =prefix + dname;
        if(dname != "." && dname != "..")
            this->filePaths.push_back(actualFile);
    }
}

void OpenFileTransferSocket(string path)
{
    ifstream f(path,ios::binary);
    if(!f)
    {
        cout<< "failed loading files"<<endl;
        return ;
    }
    Connection
}