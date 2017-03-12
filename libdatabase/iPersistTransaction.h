#ifndef __LIBDATABASE_IPERSISTTRANSACTION_H__
#define __LIBDATABASE_IPERSISTTRANSACTION_H__
#include <memory>

class iDataTransaction;
class iPersistObject;
class iPersistStatement;
class iPersistCallback;

class iPersistTransaction
{
	friend class iPersistObject;

public:
	explicit iPersistTransaction(const std::shared_ptr<iDataTransaction>& spTran) : m_spTrans(spTran) {}
    virtual ~iPersistTransaction() {}

    virtual int Commit(std::shared_ptr<iPersistCallback> spCallback) = 0;

protected:
	virtual int Insert(std::shared_ptr<iPersistObject> spObj) = 0;
	virtual int Update(std::shared_ptr<iPersistObject> spObj) = 0;
	virtual int Delete(std::shared_ptr<iPersistObject> spObj) = 0;

protected:
    virtual int BeginTransaction() = 0;
    virtual int Rollback() = 0;

	// Commit实现，放入到线程队列中执行
	virtual int CommitImpl(std::shared_ptr<iPersistCallback> spCallback) = 0;

private:
    std::shared_ptr<iDataTransaction>   m_spTrans;
};

#endif // !__LIBDATABASE_IPERSISTTRANSACTION_H__
