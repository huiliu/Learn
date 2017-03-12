#ifndef __LIBDATABASE_IPERSISTOBJECT_H__
#define __LIBDATABASE_IPERSISTOBJECT_H__
#include <memory>

class iResultSet;
class iPersistHandler;
class iPersistTransaction;
class iPersistCallback;

// 持久化数据结构
struct PersistData
{

};

// persist object
class iPersistObject
{
public:
	iPersistObject(const std::shared_ptr<iPersistHandler>& spHandler)
		: m_objectType(0)
		, m_isDirty(false)
		, m_isLoaded(false)
		, m_isPersisted(false)
		, m_spHandler(spHandler)
	{
	}
    virtual ~iPersistObject() {}

public:
	// 返回对象类型
	int GetObjectType() { return m_objectType; }
	bool IsDirty()		{ return m_isDirty; }
	bool IsLoaded()		{ return m_isLoaded; }
	bool IsPersisted()	{ return m_isPersisted; }

public:
	// 快照对象数据
	virtual PersistData SnapShot() = 0;

	// 持久化操作
    virtual int DoLoad(std::shared_ptr<iPersistTransaction> ptx, std::shared_ptr<iPersistCallback> spCallback) = 0;
    virtual int DoSave(std::shared_ptr<iPersistTransaction> ptx, std::shared_ptr<iPersistCallback> spCallback) = 0;
    virtual int DoUpdate(std::shared_ptr<iPersistTransaction> ptx, std::shared_ptr<iPersistCallback> spCallback) = 0;
    virtual int DoDestroy(std::shared_ptr<iPersistTransaction> ptx, std::shared_ptr<iPersistCallback> spCallback) = 0;

	virtual int OnLoad(iResultSet&) = 0;
	virtual int OnInsert() = 0;
	virtual int OnUpdate() = 0;
	virtual int OnDestroy() = 0;

protected:
	int		m_objectType;
	bool	m_isLoaded;
	bool	m_isDirty;
	bool	m_isPersisted;
	std::shared_ptr<iPersistHandler> m_spHandler;
};

#endif // !__LIBDATABASE_IPERSISTOBJECT_H__
