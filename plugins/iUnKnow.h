#ifndef __PLUGINS_IUNKNOW_H__
#define __PLUGINS_IUNKNOW_H__

class iUnKnow
{
public:
	iUnKnow();
	virtual ~iUnKnow() = 0;
	// ͨ��id����Plugin
	virtual long AddRef();
	virtual long DecRef();

private:
	long	m_refCount;
};

#endif