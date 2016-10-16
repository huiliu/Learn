#include "LoginPlugin.h"
#include <iostream>


LoginPlugin::LoginPlugin()
	: iPlugin(PT_LOGIN)
{
}


LoginPlugin::~LoginPlugin()
{
}

void
LoginPlugin::HandleMessage(const char* msg)
{
	std::cout << getTypeId() << " receive Message: '" << msg << std::endl;
}