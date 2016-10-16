#include "common_type.h"
#include "plugin_types.h"
#include "iPlugin.h"
#include "iPluginManager.h"
#include "LoginPlugin.h"
#include "LoadBalancePlugin.h"
#include <iostream>
#include <cassert>

iPlugin::iPlugin(PLUGIN_TYPES id)
	: m_id(id)
{
}


iPlugin::~iPlugin()
{
}


int iPlugin::Init(SP_PLUGINMANAGER& spMgr)
{
	spMgr->AddPlugin(m_id, shared_from_this());
	return 0;
}

int iPlugin::Fini()
{
	return 0;
}

void
iPlugin::HandleMessage(const char* msg)
{
	std::cout << msg << std::endl;
}


SP_PLUGIN PluginFactory(PLUGIN_TYPES id)
{
	switch (id)
	{
	case PT_LOGIN:
		return std::shared_ptr<iPlugin>(new LoginPlugin());
		break;
	case PT_LOAD_BALANCE:
		return std::shared_ptr<iPlugin>(new LoadBalancePlugin());
		break;
	default:
		assert(false);
		break;
	}
	return nullptr;
}