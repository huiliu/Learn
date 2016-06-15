#include <cassert>
#include "LoginStrategy.h"
#include <iostream>

LoginStrategy::LoginStrategy()
{
}


LoginStrategy::~LoginStrategy()
{
}

class MySQLLoginStrategy : public LoginStrategy
{
public:
	MySQLLoginStrategy(const char* host, int port);
	~MySQLLoginStrategy()
	{

	}

	virtual int Login(const char* username, const char* password);
};

MySQLLoginStrategy::MySQLLoginStrategy(const char* host, int port)
{

}

int MySQLLoginStrategy::Login(const char* username, const char* password)
{
	std::cout << "MySQL Login Strategy: \n\tUserName: " << username
		<< "\n\tPassword: " << password
		<< std::endl;
	return 0;
}

class LdapLoginStrategy : public LoginStrategy
{
public:
	LdapLoginStrategy(const char* host);

	virtual int Login(const char* username, const char* password);
};

LdapLoginStrategy::LdapLoginStrategy(const char* host)
{

}

int LdapLoginStrategy::Login(const char* username, const char* password)
{
	std::cout << "LDAP Login Strategy: \n\tUserName: " << username
		<< "\n\tPassword: " << password
		<< std::endl;
	return 0;
}


LoginStrategy* LoginStrategyFactory(LOGIN_STRATEGY_TYPE type)
{
	switch (type)
	{
	case LST_MYSQL:
		return new MySQLLoginStrategy("localhost", 3260);
		break;
	case LST_LDAP:
		return new LdapLoginStrategy("10.1.0.1");
		break;
	default:
		assert(false);
		break;
	}
	return nullptr;
}