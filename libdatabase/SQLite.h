#ifndef __LIBDATABASE_SQLITE_H__
#define __LIBDATABASE_SQLITE_H__

#include "iDatabase.h"
#include "sqlite3.h"
#include <string>

#ifdef __cplusplus
#include <iostream>
#endif

class SQLite :
    public iDataDriver
{
public:
    SQLite(const std::string& file);
    ~SQLite();

public:

    virtual iDataConnection* Connect(const std::string& file);

    virtual std::string GetVersion();
    virtual int GetMajorVersion();
    virtual int GetMinorVersion();
    virtual int GetPatchVersion();

private:
    std::string     m_DbFile;
};

class SQLiteConnection
    : public iDataConnection
{
public:
    SQLiteConnection(const std::string& file);
    ~SQLiteConnection();

public:
    virtual iDataTrasaction*    CreateTrasaction();
    virtual iDataStatement*     CreateStatement();


public:
    virtual int  Execute(const std::string& sql);
    virtual void Close();

public:
    virtual bool Ping();
    virtual std::string EscapeString(const std::string&);

public:
    sqlite3*    GetSQLite() { return m_pSQLite3; }

private:
    std::string m_DBFile;
    sqlite3*    m_pSQLite3;
};

class SQLiteStatement :
    public iDataStatement
{
public:
    SQLiteStatement(SQLiteConnection* conn);
    ~SQLiteStatement();

public:
    virtual int Prepare(const char* stmt);
    virtual int ResetPrepare(const char*);
    virtual int Finalize();

    virtual iResultSet* Execute();

public:
    virtual int BindBool(size_t idx, bool val);
    virtual int BindInt32(size_t idx, int32_t val);
    virtual int BindInt64(size_t idx, int64_t val);
    virtual int BindUInt32(size_t idx, uint32_t val);
    virtual int BindUInt64(size_t idx, uint64_t val);
    virtual int BindFloat(size_t idx, float val);
    virtual int BindDouble(size_t idx, double val);
    virtual int BindString(size_t idx, const std::string& val);

    virtual int BindBoolField(const std::string& key, bool val);
    virtual int BindInt32Field(const std::string& key, int32_t val);
    virtual int BindInt64Field(const std::string& key, int64_t val);
    virtual int BindUInt32Field(const std::string& key, uint32_t val);
    virtual int BindUInt64Field(const std::string& key, uint64_t val);
    virtual int BindFloatField(const std::string& key, float val);
    virtual int BindDoubleField(const std::string& key, double val);
    virtual int BindStringField(const std::string& key, const std::string& val);

public:
    sqlite3_stmt*   GetStatment() { return m_Stmt; }

private:
    int GetParameterIndex(const std::string& key);

private:
    SQLiteConnection*   m_pConn;
    sqlite3_stmt*       m_Stmt;
};

class SQLiteTransaction
    : public iDataTrasaction
{
public:
    SQLiteTransaction(SQLiteConnection* conn);
    ~SQLiteTransaction();

public:
    virtual int Begin();
    virtual int Commit();
    virtual int Rollback();

private:
    SQLiteConnection*   m_pConn;
};

class SQLiteResultSet
    : public iResultSet
{
public:
    SQLiteResultSet(SQLiteStatement* pStatement);
    ~SQLiteResultSet() { }

public:
    virtual int         Next();

    virtual bool        GetBool(size_t idx);
    virtual int32_t     GetInt32(size_t idx);
    virtual int64_t     GetInt64(size_t idx);
    virtual uint32_t    GetUInt32(size_t idx);
    virtual uint64_t    GetUInt64(size_t idx);
    virtual float       GetFloat(size_t idx);
    virtual double      GetDouble(size_t idx);
    virtual std::string GetString(size_t idx);

    virtual bool        GetBoolField(const std::string& colName);
    virtual int32_t     GetInt32Field(const std::string& colName);
    virtual int64_t     GetInt64Field(const std::string& colName);
    virtual uint32_t    GetUInt32Field(const std::string& colName);
    virtual uint64_t    GetUInt64Field(const std::string& colName);
    virtual float       GetFloatField(const std::string& colName);
    virtual double      GetDoubleField(const std::string& colName);
    virtual std::string GetStringField(const std::string& colName);

private:
    int     GetFieldIndex(const std::string& colName);

private:
    SQLiteStatement*    m_pStatement;
    int                 m_ColumnCount;
};

#endif // !__LIBDATABASE_SQLITE_H__
