#pragma once
#ifndef __GAME_ENTITYMANAGER_H__
#define __GAME_ENTITYMANAGER_H__
#include "CommonType.h"
#include <memory>
#include <map>


// Entity π‹¿Ì∆˜
class EntityManager
{
public:
    static EntityManager* GetInstance();
    ~EntityManager();

private:
    EntityManager();

    EntityManager(EntityManager&&) = delete;
    EntityManager(const EntityManager&) = delete;

    EntityManager operator=(const EntityManager&) = delete;
    EntityManager operator=(EntityManager&&) = delete;

public:
    ENTITY_SP CreateEntity(ENTITY_TYPE type);

    ENTITY_ID GenerateEntityId();

public:
    bool      Register(ENTITY_ID id, ENTITY_SP spEntity);
    void      Unregister(ENTITY_ID id);

    ENTITY_SP FindEntity(ENTITY_ID id);

private:
    static EntityManager* m_Instance;
    ENTITY_ID             m_iCookie;
    std::map<ENTITY_ID, ENTITY_SP> m_EntityMap;
};


#endif // !__GAME_ENTITYMANAGER_H__
