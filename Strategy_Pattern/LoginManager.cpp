#include <iostream>
#include "LoginManager.h"
#include "LoginStrategy.h"

LoginManager::LoginManager()
	: m_pLoginMethod(nullptr)
{
}


LoginManager::~LoginManager()
{
	if (nullptr != m_pLoginMethod)
	{
		delete m_pLoginMethod;
		m_pLoginMethod = nullptr;
	}
}

void LoginManager::SetLoginStrategy(LoginStrategy* pLoginStrategy)
{
	if (nullptr != m_pLoginMethod)
	{
		delete m_pLoginMethod;
	}
	m_pLoginMethod = pLoginStrategy;
}

int LoginManager::Login(const char* username, const char* password)
{
	if (nullptr != m_pLoginMethod)
	{
		return m_pLoginMethod->Login(username, password);
	}
	else
	{
		std::cerr << "Do not find Login Method!" << std::endl;
		return 1;
	}
	return -1;
}