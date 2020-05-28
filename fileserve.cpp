#include"fileserve.h"
#include"libftp.h"
#include"Connection.h"
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
    char buffer[4096];
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
    printf("List finished\n");

}

void FileServer::HandleUpload(string fileName,long long psize, int currPacket)
{
    char buffer[4096];
    printf("Starting handle file reUpload\n");

    ofstream file(fileName,ios::app); 
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
        if(readnum == -1)
        {
            printf("connection terminated\n");
            file.close();
        }
        file.write(buffer,readnum);
        packnum += readnum;
        if(packnum == psize)
            break;
    }
    file.close();
}


void FileServer::HandleUpload(string fileName,long long psize)
{
    char buffer[4096];
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
        if(readnum == -1)
        {
            printf("connection terminated\n");
            file.close();
        }
        file.write(buffer,readnum);
        packnum += readnum;
        if(packnum == psize)
            break;
    }
    file.close();

}

void FileServer::HandleDownload(string fileName)
{
    char buffer[4096];
    printf("Starting handle file Download\n");
    ifstream file(fileName,ios::binary);
    if(!file)
    {
        cout<< "failed loading files"<<endl;
        return ;
    }
    printf("openning file success\n");
     struct stat file_stat;
    stat(fileName.c_str(), &file_stat);
    int fsize = file_stat.st_size;
    while(fsize >0 )
    {
        int osize = fsize>4096? 4096:fsize;
        file.read(buffer,osize);
        write(socket,buffer,osize);
        fsize -=osize;
    }
    file.close();
    printf("finished sending files");

    
}

void FileServer::HandleSize(string fileName)
{
    char buffer[4096];
    struct stat file_stat;
    int stat_status = stat(fileName.c_str(), &file_stat);
    if(stat_status != 0)
    {
        printf("File not found\n");
        return ;
    }
    memset(buffer,0,4096);
    sprintf(buffer,"%d\n",file_stat.st_size);
    printf("get buffer size %s\n",buffer);
    write(socket,buffer,strlen(buffer));
    printf("size success\n");
}

bool FileServer::HandleCWD(string Directory)
{
    struct stat file_stat;
    int stat_status = stat(Directory.c_str(), &file_stat);
    if(stat_status != 0)
    {
        printf("Dir not found \n");
        return false;
    }
    if(S_ISDIR(file_stat.st_mode))
    {
        this->currentPath = Directory;
        return true;
    }
}