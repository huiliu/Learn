#ifndef __GAME_GAMEUSERMANAGER_H__
#define __GAME_GAMEUSERMANAGER_H__
#include "CommonType.h"


class GameUserManager
{
public:
    static GameUserManager* GetInstance()
    {
        if (nullptr == m_Instance )
        {
            m_Instance = new GameUserManager();
        }

        return m_Instance;
    }

public:
    GAMEUSER_SP CreateUser();

private:
    GameUserManager() {}
    ~GameUserManager() {}

private:
    static GameUserManager* m_Instance;
};

#endif // !__GAME_GAMEUSERMANAGER_H__
