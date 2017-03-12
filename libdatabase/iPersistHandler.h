#ifndef __LIBDATABASE_IPERSISTHANDLER_H__
#define __LIBDATABASE_IPERSISTHANDLER_H__
#include <memory>

class iDataConnection;
class iPersistObject;
class iPersistTransaction;
class iPersistStatement;

class iPersistHandler
{
public:
    virtual ~iPersistHandler() {}

    virtual std::shared_ptr<iPersistStatement> CreateStatement() = 0;
    virtual std::shared_ptr<iPersistTransaction> CreateTransaction() = 0;

public:
	virtual int Insert(std::shared_ptr<iPersistTransaction> spTrans, std::shared_ptr<iPersistObject> spObj) = 0;
	virtual int Update(std::shared_ptr<iPersistTransaction> spTrans, std::shared_ptr<iPersistObject> spObj) = 0;
	virtual int Delete(std::shared_ptr<iPersistTransaction> spTrans, std::shared_ptr<iPersistObject> spObj) = 0;

private:
    std::shared_ptr<iDataConnection> m_spConn;
};

#endif // !__LIBDATABASE_IPERSISTHANDLER_H__
