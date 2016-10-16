#include "iPluginManager.h"
#include "iPlugin.h"
#include <iostream>

iPluginManager::~iPluginManager()
{
}

bool iPluginManager::PluginHasRegistered(PLUGIN_TYPES id)
{
	return m_mPlugins.find(id) != m_mPlugins.end();
}

std::tuple<int, SP_PLUGIN> iPluginManager::FindPlugin(PLUGIN_TYPES id)
{
	if (PluginHasRegistered(id))
	{
		return std::make_tuple(0, m_mPlugins.find(id)->second);
	}

	return std::make_tuple(1, nullptr);
}


int iPluginManager::AddPlugin(PLUGIN_TYPES id, SP_PLUGIN& spPlugin)
{
	if (PluginHasRegistered(id))
	{
		std::cout << "the plugin has registered!" << std::endl;
	}
	m_mPlugins.emplace(id, spPlugin);

	return 0;
}


int iPluginManager::Remove(PLUGIN_TYPES id)
{
	int ret = 1;	// ²å¼þÎ´×¢²á
	if (PluginHasRegistered(id))
	{
		m_mPlugins.erase(id);
		ret = 0;
	}
	return ret;
}

void
iPluginManager::PublishMessage(const char* msg)
{
	for (auto& item : m_mPlugins)
	{
		if (nullptr != item.second)
			item.second->HandleMessage(msg);
	}
}

void iPluginManager::DeletePlugins()
{
	m_mPlugins.clear();
}
