#include "EntityManager.h"


EntityManager* EntityManager::m_Instance = nullptr;

EntityManager::EntityManager()
    : m_iCookie(0);
{
}


EntityManager::~EntityManager()
{
    m_EntityMap.clear();
}

ENTITY_SP EntityManager::CreateEntity(ENTITY_TYPE type)
{
    return ENTITY_SP();
}

ENTITY_ID EntityManager::GenerateEntityId()
{
    return ++m_iCookie;
}

bool EntityManager::Register(ENTITY_ID id, ENTITY_SP spEntity)
{
    auto it = FindEntity(id);
    if (it)
    {
        // registered!
        ;
    }

    m_EntityMap[id] = spEntity;
    return 0;
}

EntityManager* EntityManager::GetInstance()
{
    if (nullptr == m_Instance)
    {
        m_Instance = new EntityManager();
    }

    return m_Instance;
}

void EntityManager::Unregister(ENTITY_ID id)
{
    m_EntityMap.erase(id);
}

ENTITY_SP EntityManager::FindEntity(ENTITY_ID id)
{
    auto it = m_EntityMap.find(id);
    if (m_EntityMap.end() != it)
    {
        return it->second;
    }
    return nullptr;
}
