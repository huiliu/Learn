#pragma once

class LoginStrategy;

class LoginManager
{
public:
	LoginManager();
	~LoginManager();

	int		Login(const char* username, const char* password);

	void	SetLoginStrategy(LoginStrategy* pLoginStrategy);
private:
	LoginStrategy*	m_pLoginMethod;
};

