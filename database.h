#ifndef __MYSQL__DB___
#define __MYSQL__DB___
#include "/usr/include/mysql/mysql.h"
#include<vector>
#include<string>
#include<map>
using std::string;
using std::vector;
using std::map;
class DataBase
{
    vector<string> userName;
    vector<string> passWord;
    DataBase();
    DataBase(DataBase&) = delete;
    DataBase& operator= (const DataBase&)=delete;
    static DataBase* m_database_ptr;
public:
    static DataBase* GetInstance()
    {
        if(m_database_ptr == nullptr)
        {
            m_database_ptr = new DataBase;
        }
        return m_database_ptr;
    }

    bool checkUserNameOK(string usern);
    bool checkPassWordOK(string usern,string passw);
};


#endif