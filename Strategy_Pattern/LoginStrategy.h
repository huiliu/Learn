#pragma once
// µÇÂ½ÑéÖ¤

enum LOGIN_STRATEGY_TYPE
{
		LST_MYSQL,
		LST_LDAP,
};

class LoginStrategy
{
public:
	LoginStrategy();
	virtual ~LoginStrategy();

	virtual int		Login(const char* username, const char* password) = 0;
};

LoginStrategy* LoginStrategyFactory(LOGIN_STRATEGY_TYPE type);