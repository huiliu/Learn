#pragma once
#include "iPlugin.h"
class LoadBalancePlugin :
	public iPlugin
{
public:
	LoadBalancePlugin();
	~LoadBalancePlugin();

	virtual void HandleMessage(const char* msg);
};

