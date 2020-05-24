#ifndef __main_ftpserver__
#define __main_ftpserver__

#include"Connection.h"
#include"database.h"
#include"libftp.h"
#include"fileserve.h"

bool Login(int socket);
void Serv(int socket);

#endif