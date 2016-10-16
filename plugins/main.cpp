// plugins.cpp : 定义控制台应用程序的入口点。
//

#include "Master.h"
#include "LoginPlugin.h"
#include "LoadBalancePlugin.h"

int main()
{
	std::shared_ptr<iPluginManager> spMaster(new Master());

	SP_PLUGIN spLogin = PluginFactory(PT_LOGIN);
	SP_PLUGIN spLoadBalance = PluginFactory(PT_LOAD_BALANCE);
	
	spLogin->Init(spMaster);
	spLoadBalance->Init(spMaster);
    
	spMaster->PublishMessage("Hello come from master!");
	return 0;
}

