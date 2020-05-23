#include"database.h"
#include<stdio.h>

DataBase* DataBase::m_database_ptr = nullptr;

DataBase::DataBase()
{
    if (mysql_library_init(0, NULL, NULL)) 
    {
        fprintf(stderr, "could not initialize MySQL client library\n");
        exit(1);
    }

    
    MYSQL conn;
    
    MYSQL_ROW result_row;
    mysql_init(&conn);
    if(mysql_real_connect(&conn,"localhost","root","","FTPServer",0,NULL,CLIENT_FOUND_ROWS)) //"root":数据库管理员 "":root密码 "test":数据库的名字
    {
        printf("connect success!\n");
        char sqlstr[300];
        sprintf(sqlstr,"SELECT * FROM Users");
        int res=mysql_query(&conn,sqlstr);
        if(res)
            printf("Error on reading users data\n");
        MYSQL_RES *rest = mysql_store_result(&conn);
        int row = mysql_num_rows(rest) + 1;

        for (int i = 1; i < row; i++)
        {
            result_row = mysql_fetch_row(rest);
            printf("%s",result_row[0]);
            this->userName.push_back(string(result_row[0]));
            this->passWord.push_back(string(result_row[1]));
        }  

        mysql_free_result(rest);

    }
    mysql_close(&conn);

    mysql_library_end();
}

bool DataBase::checkUserNameOK(string usern)
{
    printf("checking if %s user exist\n",usern.c_str());
    int userSize = this->userName.size();
    for(int i=0;i<userSize;i++)
    {
        if(this->userName[i] == usern)
            return true;
    }
    return false;
}

bool DataBase::checkPassWordOK(string usern,string passw)
{
    int userSize = this->userName.size();
     for(int i=0;i<userSize;i++)
    {
        if(this->userName[i] == usern)
            if(this->passWord[i] == passw)
            {
                printf("password correct\n");
                return true;
            }
            else
            {
                return false;
            }
    }
    return false;
}