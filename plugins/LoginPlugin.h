#pragma once
#include "iPlugin.h"
class LoginPlugin :
	public iPlugin
{
public:
	LoginPlugin();
	~LoginPlugin();

	virtual void HandleMessage(const char* msg);
};

