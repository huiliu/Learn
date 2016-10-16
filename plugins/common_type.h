#pragma once
#ifndef __PLUGINS_COMMON_TYPE_H__
#define __PLUGINS_COMMON_TYPE_H__
#include <memory>

class iPlugin;
class iPluginManager;

typedef std::shared_ptr<iPlugin>	SP_PLUGIN;
typedef std::shared_ptr<iPluginManager>		SP_PLUGINMANAGER;
#endif