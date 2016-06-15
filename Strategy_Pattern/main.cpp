// Strategy_Pattern.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "LoginManager.h"
#include "LoginStrategy.h"


int main()
{
	LoginManager* pLoginMgr = new LoginManager();

	pLoginMgr->Login("hello", "world");

	pLoginMgr->SetLoginStrategy(LoginStrategyFactory(LST_MYSQL));
	pLoginMgr->Login("hello", "world");

	pLoginMgr->SetLoginStrategy(LoginStrategyFactory(LST_LDAP));
	pLoginMgr->Login("hello", "world");

    return 0;
}

