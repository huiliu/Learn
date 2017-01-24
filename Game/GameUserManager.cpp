#include "GameUserManager.h"
#include "GameUser.h"
#include "EntityManager.h"


GameUserManager* GameUserManager::m_Instance = new GameUserManager();

GameUserManager::GameUserManager()
{
}


GameUserManager::~GameUserManager()
{
}

GAMEUSER_SP GameUserManager::CreateUser()
{
    ENTITY_ID eid = EntityManager::GetInstance()->GenerateEntityId();
    return GAMEUSER_SP(new GameUser(eid));
}
