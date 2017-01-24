// Game.cpp : 定义控制台应用程序的入口点。
//

#include "EntityManager.h"
#include "GameMap.h"
#include "GameUser.h"
#include <iostream>
#include <memory>

int main()
{
    ENTITY_ID uid = 1;
    ENTITY_ID mid = 10001;

    std::shared_ptr<GameMap> spMap(new GameMap(mid));
    GAMEUSER_SP spUser(new GameUser(uid));
    spUser->SetName("joy");

    EntityManager::GetInstance()->Register(uid, spUser);

    spMap->EnterMap(uid, MapPos(1, 2));
    MoveResult result = spMap->MoveTo(uid, 1, MapPos(10, 9));

    EntityManager::GetInstance()->Unregister(uid);
    return 0;
}
