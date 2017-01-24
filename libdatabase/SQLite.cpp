#include "SQLite.h"
#include <iostream>
#include <cassert>


SQLite::SQLite(const std::string & file)
    : m_DbFile(file)
{
}

SQLite::~SQLite()
{
}

iDataConnection * SQLite::Connect(const std::string & file)
{
    return new SQLiteConnection(file);
}

std::string SQLite::GetVersion()
{
    return std::string();
}

int SQLite::GetMajorVersion()
{
    return 0;
}

int SQLite::GetMinorVersion()
{
    return 0;
}

int SQLite::GetPatchVersion()
{
    return 0;
}

SQLiteStatement::SQLiteStatement(SQLiteConnection * conn)
    : m_pConn(conn)
    , m_Stmt(nullptr)
{
}

SQLiteStatement::~SQLiteStatement()
{
    Finalize();
}

int SQLiteStatement::Prepare(const char * stmt)
{
    assert(nullptr != stmt);
    if (nullptr!=stmt)
    {
        return sqlite3_prepare(m_pConn->GetSQLite(), stmt, -1, &m_Stmt, nullptr);
    }

    // TODO: 此返回值需要斟酌
    return SQLITE_FAIL;
}

int SQLiteStatement::ResetPrepare(const char *stmt)
{
    assert(nullptr != m_Stmt);

    int ret = sqlite3_reset(m_Stmt);
    if (SQLITE_OK != ret)
    {
        return ret;
    }

    return Prepare(stmt);
}

int SQLiteStatement::Finalize()
{
    assert(nullptr != m_Stmt);
    int ret = sqlite3_finalize(m_Stmt);
    if (SQLITE_OK != ret)
    {
        std::cout << sqlite3_errmsg(m_pConn->GetSQLite()) << std::endl;
    }
    return ret;
}

iResultSet* SQLiteStatement::Execute()
{
    assert(nullptr != m_Stmt);
    int ret = sqlite3_step(m_Stmt);

    return new SQLiteResultSet(this);
}

int SQLiteStatement::BindBool(size_t idx, bool val)
{
    assert(nullptr != m_Stmt);
    return sqlite3_bind_int(m_Stmt, idx, val ? 1 : 0);
    return 0;
}

int SQLiteStatement::BindInt32(size_t idx, int32_t val)
{
    assert(nullptr != m_Stmt);
    return sqlite3_bind_int(m_Stmt, idx, val);
    return 0;
}

int SQLiteStatement::BindInt64(size_t idx, int64_t val)
{
    assert(nullptr != m_Stmt);
    return sqlite3_bind_int64(m_Stmt, idx, val);
    return 0;
}

int SQLiteStatement::BindUInt32(size_t idx, uint32_t val)
{
    assert(false);
    return 0;
}

int SQLiteStatement::BindUInt64(size_t idx, uint64_t val)
{
    assert(false);
    return 0;
}

int SQLiteStatement::BindFloat(size_t idx, float val)
{
    BindDouble(idx, val);
    return 0;
}

int SQLiteStatement::BindDouble(size_t idx, double val)
{
    assert(nullptr != m_Stmt);
    return sqlite3_bind_double(m_Stmt, idx, val);
}

int SQLiteStatement::BindString(size_t idx, const std::string& val)
{
    assert(nullptr != m_Stmt);
    return sqlite3_bind_text(m_Stmt, idx, val.data(), -1, nullptr);
    return 0;
}

int SQLiteStatement::BindBoolField(const std::string & key, bool val)
{
    assert(nullptr != m_Stmt);
    int idx = GetParameterIndex(key);
    return BindBool(idx, val);
}

int SQLiteStatement::BindInt32Field(const std::string & key, int32_t val)
{
    assert(nullptr != m_Stmt);
    int idx = GetParameterIndex(key);
    return BindInt32(idx, val);
}

int SQLiteStatement::BindInt64Field(const std::string & key, int64_t val)
{
    assert(nullptr != m_Stmt);
    int idx = GetParameterIndex(key);
    return BindInt64(idx, val);
}

int SQLiteStatement::BindUInt32Field(const std::string & key, uint32_t val)
{
    assert(false);
    return 0;
}

int SQLiteStatement::BindUInt64Field(const std::string & key, uint64_t val)
{
    assert(false);
    return 0;
}

int SQLiteStatement::BindFloatField(const std::string & key, float val)
{
    assert(false);
    return 0;
}

int SQLiteStatement::BindDoubleField(const std::string & key, double val)
{
    assert(nullptr != m_Stmt);
    int idx = GetParameterIndex(key);
    return BindDouble(idx, val);
}

int SQLiteStatement::BindStringField(const std::string & key, const std::string & val)
{
    assert(nullptr != m_Stmt);
    int idx = GetParameterIndex(key);
    return BindString(idx, val);
}

int SQLiteStatement::GetParameterIndex(const std::string & key)
{
    assert(nullptr != m_Stmt);
    int idx = sqlite3_bind_parameter_index(m_Stmt, key.data());
    if (0==idx)
    {
        assert(false);
        // 没有找到field
    }
    
    return idx;
}

SQLiteConnection::SQLiteConnection(const std::string & file)
    : m_DBFile(file)
    , m_pSQLite3(nullptr)
{
    int ret = sqlite3_open(file.data(), &m_pSQLite3);
    if (SQLITE_OK != ret)
    {
        assert(false);
        // 输出错误
    }
}

SQLiteConnection::~SQLiteConnection()
{
    Close();
}

iDataTrasaction * SQLiteConnection::CreateTrasaction()
{
    return new SQLiteTransaction(this);
}

iDataStatement * SQLiteConnection::CreateStatement()
{
    return new SQLiteStatement(this);
}

int SQLiteConnection::Execute(const std::string & sql)
{
    int ret = sqlite3_exec(m_pSQLite3, sql.data(), nullptr, nullptr, nullptr);
    if (SQLITE_OK != ret)
    {
        assert(false);
        // 出错提示
    }
    return ret;
    return 0;
}

void SQLiteConnection::Close()
{
    assert(nullptr != m_pSQLite3);
    if (nullptr != m_pSQLite3)
    {
        sqlite3_close(m_pSQLite3);
    }
}

bool SQLiteConnection::Ping()
{
    return true;
}

std::string SQLiteConnection::EscapeString(const std::string & val)
{
    return val;
}

SQLiteTransaction::SQLiteTransaction(SQLiteConnection * conn)
    : m_pConn(conn)
{
}

SQLiteTransaction::~SQLiteTransaction()
{
}

int SQLiteTransaction::Begin()
{
    return m_pConn->Execute("BEGIN TRANSACTION");
}

int SQLiteTransaction::Commit()
{
    return m_pConn->Execute("COMMIT");
}

int SQLiteTransaction::Rollback()
{
    return m_pConn->Execute("ROLLBACK");
}

SQLiteResultSet::SQLiteResultSet(SQLiteStatement * pStatement)
    : m_pStatement(pStatement)
    , m_ColumnCount(0)
{
    assert(nullptr != m_pStatement);
    m_ColumnCount = sqlite3_column_count(m_pStatement->GetStatment());
}

int SQLiteResultSet::Next()
{
    // TODO: 将返回值重新包装定义
    return sqlite3_step(m_pStatement->GetStatment());
}

bool SQLiteResultSet::GetBool(size_t idx)
{
    assert(idx >= 0 && idx < m_ColumnCount);
    return static_cast<bool>(sqlite3_column_int(m_pStatement->GetStatment(), idx));
}

int32_t SQLiteResultSet::GetInt32(size_t idx)
{
    assert(idx >= 0 && idx < m_ColumnCount);
    return sqlite3_column_int(m_pStatement->GetStatment(), idx);
}

int64_t SQLiteResultSet::GetInt64(size_t idx)
{
    assert(idx >= 0 && idx < m_ColumnCount);
    return sqlite3_column_int64(m_pStatement->GetStatment(), idx);
}

uint32_t SQLiteResultSet::GetUInt32(size_t idx)
{
    assert(false);
    return uint32_t();
}

uint64_t SQLiteResultSet::GetUInt64(size_t idx)
{
    assert(false);
    return uint64_t();
}

float SQLiteResultSet::GetFloat(size_t idx)
{
    return GetDouble(idx);
}

double SQLiteResultSet::GetDouble(size_t idx)
{
    assert(idx >= 0 && idx < m_ColumnCount);
    return sqlite3_column_double(m_pStatement->GetStatment(), idx);
}

std::string SQLiteResultSet::GetString(size_t idx)
{

    assert(idx >= 0 && idx < m_ColumnCount);
    int sz = sqlite3_column_bytes(m_pStatement->GetStatment(), idx);
    const unsigned char* head = sqlite3_column_text(m_pStatement->GetStatment(), idx);
    return std::string(head, head + sz);
}

bool SQLiteResultSet::GetBoolField(const std::string & colName)
{
    return GetBool(GetFieldIndex(colName));
}

int32_t SQLiteResultSet::GetInt32Field(const std::string & colName)
{
    return GetInt32(GetFieldIndex(colName));
}

int64_t SQLiteResultSet::GetInt64Field(const std::string & colName)
{
    return GetInt64(GetFieldIndex(colName));
}

uint32_t SQLiteResultSet::GetUInt32Field(const std::string & colName)
{
    return GetUInt32(GetFieldIndex(colName));
}

uint64_t SQLiteResultSet::GetUInt64Field(const std::string & colName)
{
    return GetUInt64(GetFieldIndex(colName));
}

float SQLiteResultSet::GetFloatField(const std::string & colName)
{
    return GetFloat(GetFieldIndex(colName));
}

double SQLiteResultSet::GetDoubleField(const std::string & colName)
{
    return GetDouble(GetFieldIndex(colName));
}

std::string SQLiteResultSet::GetStringField(const std::string & colName)
{
    return GetString(GetFieldIndex(colName));
}

int SQLiteResultSet::GetFieldIndex(const std::string & colName)
{
    const char* _colName = nullptr;
    for (size_t i = 0; i < m_ColumnCount; i++)
    {
        _colName = sqlite3_column_name(m_pStatement->GetStatment(), i);
        if (nullptr != _colName &&
            sqlite3_stricmp(_colName, colName.data()) == 0 )
        {
            return i;
        }
    }

    return -1;
}
