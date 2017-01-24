#pragma once
#ifndef __GAME_BLOCK_H__
#define __GAME_BLOCK_H__
#include "CommonType.h"
#include <map>

class Block
{
public:
    Block(const MapPos& pos, BlockSize& sz);
    ~Block();

public:
    bool Attach(ENTITY_ID id);
    bool Detach(ENTITY_ID id);

public:
    ENTITY_ID_VEC   GetAllEntities() const;

private:
    bool IsInBlock(ENTITY_ID id);

private:
    MapPos    m_Pos;
    BlockSize m_BlockSize;
    std::map<ENTITY_ID, bool> m_Entities;
};

#endif // !__GAME_BLOCK_H__
