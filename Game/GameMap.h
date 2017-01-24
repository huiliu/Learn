#pragma once
#ifndef __GAME_GAMEMAP_H__
#define __GAME_GAMEMAP_H__
#include "CommonType.h"
#include "iGameEntity.h"
#include <vector>
#include <map>
//
// File: GameMap.h
// Auth: Liu Hui <hui.liu.e@gmail.com>
// Description:
//  游戏地图的一个抽象,将地图划分为格式，格子由Block表示，游戏对象被存储在Block中

class Block;

class GameMap : public iGameEntity
{
public:
    GameMap(ENTITY_ID mid);
    ~GameMap();

public:
    virtual int Init();
    virtual int Fini();

public:
    bool LoadData();

public:
    // 进入地图
    MoveResult EnterMap(ENTITY_ID id, MapPos dest);
    // 离开地图
    MoveResult LeaveMap(ENTITY_ID id, MapPos dest);
    // 移动至dest
    MoveResult MoveTo(ENTITY_ID id, int iSpeed, MapPos dest);

private:
    // 取得指定点所在格子ID
    size_t GetBlockIdByPos(const MapPos& pos);

    // 取得可能观察到指定坐标点的对象列表
    ENTITY_ID_VEC GetBroadcastEntities(const MapPos& pos);

private:
    // 是否可以到达pos
    bool CanArrived(ENTITY_ID id, const MapPos& pos);

private:
    ENTITY_ID m_Id;     // 地图ID
    BlockSize m_MapSize;
    BlockSize m_BlockSize;

    size_t m_RowCount;
    size_t m_ColCount;

    std::vector<Block> m_BlockVec;
    std::map<ENTITY_ID, int>    m_Entities; // 记录entity所在的block
};

#endif // !__GAME_GAMEMAP_H__
