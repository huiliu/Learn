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
//  ��Ϸ��ͼ��һ������,����ͼ����Ϊ��ʽ��������Block��ʾ����Ϸ���󱻴洢��Block��

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
    // �����ͼ
    MoveResult EnterMap(ENTITY_ID id, MapPos dest);
    // �뿪��ͼ
    MoveResult LeaveMap(ENTITY_ID id, MapPos dest);
    // �ƶ���dest
    MoveResult MoveTo(ENTITY_ID id, int iSpeed, MapPos dest);

private:
    // ȡ��ָ�������ڸ���ID
    size_t GetBlockIdByPos(const MapPos& pos);

    // ȡ�ÿ��ܹ۲쵽ָ�������Ķ����б�
    ENTITY_ID_VEC GetBroadcastEntities(const MapPos& pos);

private:
    // �Ƿ���Ե���pos
    bool CanArrived(ENTITY_ID id, const MapPos& pos);

private:
    ENTITY_ID m_Id;     // ��ͼID
    BlockSize m_MapSize;
    BlockSize m_BlockSize;

    size_t m_RowCount;
    size_t m_ColCount;

    std::vector<Block> m_BlockVec;
    std::map<ENTITY_ID, int>    m_Entities; // ��¼entity���ڵ�block
};

#endif // !__GAME_GAMEMAP_H__
