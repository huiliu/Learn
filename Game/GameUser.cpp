#include "GameUser.h"
#include <cassert>



GameUser::GameUser(ENTITY_ID uid)
    : m_Name()
    , m_iSpeed(0)
{
    SetId(uid);
}


GameUser::~GameUser()
{
}

int GameUser::Init()
{
    return 0;
}

int GameUser::Fini()
{
    return 0;
}

void GameUser::SetName(const std::string & name)
{
    m_Name = name;
}

void GameUser::HandleMoveTo(MapPos pos)
{
}
