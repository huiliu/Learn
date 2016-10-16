#ifndef __PLUGINS_IPLUGINMANAGER_H__
#define __PLUGINS_IPLUGINMANAGER_H__

#include "iUnKnow.h"
#include "common_type.h"
#include "plugin_types.h"
#include <map>
#include <tuple>
#include <memory>

class iPlugin;

class iPluginManager :
	public iUnKnow
{
public:
	virtual ~iPluginManager() = 0;
	
	std::tuple<int, SP_PLUGIN> FindPlugin(PLUGIN_TYPES id);
	int AddPlugin(PLUGIN_TYPES id, SP_PLUGIN& spPlugin);
	int Remove(PLUGIN_TYPES id);
	void DeletePlugins();

	virtual void PublishMessage(const char* msg);

private:
	bool PluginHasRegistered(PLUGIN_TYPES id);

private:
	typedef std::map<PLUGIN_TYPES, SP_PLUGIN> PLUGINS_MAP;

	PLUGINS_MAP		m_mPlugins;
};



#endif