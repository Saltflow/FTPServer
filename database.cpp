#include"database.h"
#include<stdio.h>
int revokeDataBase()
{
    //初始化库,非多线程程序可以省略，mysql_init()调用这个函数
    if (mysql_library_init(0, NULL, NULL)) {
        fprintf(stderr, "could not initialize MySQL client library\n");
        exit(1);
    }

    MYSQL_RES *rest;
    MYSQL conn;
    MYSQL_FIELD *field;
    MYSQL_ROW result_row;
    int res,i,j,row,column;
    mysql_init(&conn);
    if(mysql_real_connect(&conn,"localhost","root","","FTPServer",0,NULL,CLIENT_FOUND_ROWS)) //"root":数据库管理员 "":root密码 "test":数据库的名字
    {
        printf("connect success!\n");
        char sqlstr[300];
        int id1=111;
        sprintf(sqlstr,"SELECT * FROM Users");
        res=mysql_query(&conn,sqlstr);
        //res=mysql_query(&conn,"insert into dept values(11,'reserach','new york')");
        if(res)
        {
            printf("insert error\n");
        }
        else
        {
            printf("insert OK\n");
        }
        /*这句话是设置查询编码为utf8，这样支持中文*/
    //    mysql_query(&conn, "set names utf8");
        //查询数据
  //      res = mysql_query(&conn,"select * from dept");
   //     rest = mysql_store_result(&conn);
        //取得結果的行数和列数
    //    column = mysql_num_fields(rest);
    //    row = mysql_num_rows(rest) + 1;
 //       printf("查询到 %d 行 \n", row);

        //输出結果的字段名
        for (i = 0; (field = mysql_fetch_field(rest)); i++)
            printf("%s\t", field->name);
        printf("\n");
        //按行输出結果
        for (i = 1; i < row; i++)
        {
            result_row = mysql_fetch_row(rest);
            for (j = 0; j < column; j++)
                printf("%s\t", result_row[j]);
            printf("\n");  
        }  

        mysql_free_result(rest);
        //删除数据
        res=mysql_query(&conn,"delete from dept where deptno = 11");
        //res=mysql_commit(&conn);
        if(res)
        {
            printf("delete error\n");
        }
        else
        {
            printf("delete OK\n");
        }

    }
    mysql_close(&conn);
    //内存资源回收
    mysql_library_end();
}
