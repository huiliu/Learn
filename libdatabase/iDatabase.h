#ifndef __LIBDATABASE_IDATABASE_H__
#define __LIBDATABASE_IDATABASE_H__

#include <string>

class iDataResult;
class iDataStatement;
class iDataTrasaction;
class iResultSet;

class iDataConnection
{
public:
    virtual ~iDataConnection() {}

public:
    virtual iDataTrasaction*    CreateTrasaction() = 0;
    virtual iDataStatement*     CreateStatement() = 0;

    virtual void Close()    = 0;

public:
    virtual int     Execute(const std::string& sql) = 0;

public:
    virtual bool Ping() = 0;
    virtual std::string EscapeString(const std::string&) = 0;
};

//
class iDataDriver
{
public:
    virtual ~iDataDriver() {}

public:
    virtual iDataConnection* Connect(const std::string& conn) = 0;

    virtual std::string GetVersion() = 0;
    virtual int GetMajorVersion() = 0;
    virtual int GetMinorVersion() = 0;
    virtual int GetPatchVersion() = 0;
};

class iDataTrasaction
{
public:
    virtual ~iDataTrasaction() {}

public:

    virtual int Begin() = 0;
    virtual int Commit() = 0;
    virtual int Rollback() = 0;
};

class iDataStatement
{
public:
    virtual ~iDataStatement() { }

public:

    virtual int Prepare(const char* stmt) = 0;
    virtual int ResetPrepare(const char*) = 0;
    virtual int Finalize() = 0;

    virtual iResultSet* Execute() = 0;

public:
    virtual int BindBool(size_t idx, bool val) = 0;
    virtual int BindInt32(size_t idx, int32_t val) = 0;
    virtual int BindInt64(size_t idx, int64_t val) = 0;
    virtual int BindUInt32(size_t idx, uint32_t val) = 0;
    virtual int BindUInt64(size_t idx, uint64_t val) = 0;
    virtual int BindFloat(size_t idx, float val) = 0;
    virtual int BindDouble(size_t idx, double val) = 0;
    virtual int BindString(size_t idx, const std::string& val) = 0;

    virtual int BindBoolField(const std::string& idx, bool val) = 0;
    virtual int BindInt32Field(const std::string& key, int32_t val) = 0;
    virtual int BindInt64Field(const std::string& key, int64_t val) = 0;
    virtual int BindUInt32Field(const std::string& key, uint32_t val) = 0;
    virtual int BindUInt64Field(const std::string& key, uint64_t val) = 0;
    virtual int BindFloatField(const std::string& key, float val) = 0;
    virtual int BindDoubleField(const std::string& key, double val) = 0;
    virtual int BindStringField(const std::string& key, const std::string& val) = 0;
};

class iResultSet
{
public:
    virtual ~iResultSet() { }

public:
    virtual int         Next() = 0;

    virtual bool        GetBool(size_t idx) = 0;
    virtual int32_t     GetInt32(size_t idx) = 0;
    virtual int64_t     GetInt64(size_t idx) = 0;
    virtual uint32_t    GetUInt32(size_t idx) = 0;
    virtual uint64_t    GetUInt64(size_t idx) = 0;
    virtual float       GetFloat(size_t idx) = 0;
    virtual double      GetDouble(size_t idx) = 0;
    virtual std::string GetString(size_t idx) = 0;

    virtual bool        GetBoolField(const std::string& colName) = 0;
    virtual int32_t     GetInt32Field(const std::string& colName) = 0;
    virtual int64_t     GetInt64Field(const std::string& colName) = 0;
    virtual uint32_t    GetUInt32Field(const std::string& colName) = 0;
    virtual uint64_t    GetUInt64Field(const std::string& colName) = 0;
    virtual float       GetFloatField(const std::string& colName) = 0;
    virtual double      GetDoubleField(const std::string& colName) = 0;
    virtual std::string GetStringField(const std::string& colName) = 0;
};

#endif // !__LIBDATABASE_IDATABASE_H__
