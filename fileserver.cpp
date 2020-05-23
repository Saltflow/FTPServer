#include"fileserve.h"

FileDirectory::FileDirectory(string path)
{
    char buffer[2048];
    currentPath = path;
    DIR* dir;
    struct dirent *mdirent;
    dir = opendir(path.c_str());
    char* offset = buffer;
    while((mdirent = readdir(dir) ) != NULL)
    {
        string actualFile =path + string("/") + string(mdirent -> d_name);
        this->filePaths.push_back(actualFile);
    }
}

void OpenFileTransferSocket(string path)
{

}