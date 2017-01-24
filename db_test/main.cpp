// db_test.cpp : 定义控制台应用程序的入口点。
//

#include "SQLite.h"
#include <iostream>

int main()
{
    SQLite mySqlite("test.db");
    iDataConnection* pconn = mySqlite.Connect("test.db");

    pconn->Execute("CREATE TABLE test(id int)");
    pconn->Execute("INSERT INTO test VALUES(10)");
    pconn->Execute("INSERT INTO test VALUES(20)");
    pconn->Execute("INSERT INTO test VALUES(30)");
    pconn->Execute("INSERT INTO test VALUES(10)");

    iDataStatement* pStatement = pconn->CreateStatement();

    pStatement->Prepare("SELECT * FROM test");

    pStatement->BindInt32(1, 10);

    iResultSet* result= pStatement->Execute();

    std::cout << result->GetInt32(0) << std::endl;
    result->Next();
    std::cout << result->GetInt32(0) << std::endl;
    result->Next();
    std::cout << result->GetInt32(0) << std::endl;
    result->Next();
    std::cout << result->GetInt32(0) << std::endl;
    result->Next();
    std::cout << result->GetInt32(0) << std::endl;
    result->Next();
    std::cout << result->GetInt32(0) << std::endl;
    result->Next();

    pconn->Close();
    return 0;
}

