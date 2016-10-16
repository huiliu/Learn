#include "LoadBalancePlugin.h"
#include <iostream>

LoadBalancePlugin::LoadBalancePlugin()
	: iPlugin(PT_LOAD_BALANCE)
{
}


LoadBalancePlugin::~LoadBalancePlugin()
{
}

void
LoadBalancePlugin::HandleMessage(const char* msg)
{
	std::cout << getTypeId() << " receive message'" << msg << "'" << std::endl;
}