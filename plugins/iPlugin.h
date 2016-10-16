#ifndef __PLUGINS_IPLUGIN_H__
#define __PLUGINS_IPLUGIN_H__

#include "iUnKnow.h"
#include "common_type.h"
#include "plugin_types.h"
#include <memory>

class iPluginManager;

class iPlugin :
	public iUnKnow,
	public std::enable_shared_from_this<iPlugin>
{
public:
	iPlugin(PLUGIN_TYPES id);
	virtual ~iPlugin() = 0;

	virtual int Init(SP_PLUGINMANAGER& pMgr);
	virtual int Fini();

	virtual void HandleMessage(const char* msg);

	PLUGIN_TYPES	getTypeId() const { return m_id; }

private:
	PLUGIN_TYPES		m_id;	// ²å¼þID
};

SP_PLUGIN PluginFactory(PLUGIN_TYPES id);

#endif