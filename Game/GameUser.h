#pragma once
#ifndef __GAME_GAMEUSER_H__
#define __GAME_GAMEUSER_H__
#include "iGameEntity.h"
#include <string>
#include <memory>

class GameUser :
    public iGameEntity
{
public:
    GameUser(ENTITY_ID uid);
    ~GameUser();

public:
    virtual int Init();
    virtual int Fini();

public:
    void SetName(const std::string& name);
    std::string GetName() const { return m_Name; }

public:
    void HandleMoveTo(MapPos pos);

private:
    std::string m_Name;
    int m_iSpeed;
};

#endif // !__GAME_GAMEUSER_H__
