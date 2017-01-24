#ifndef __GAME_COMMONTYPE_H__
#define __GAME_COMMONTYPE_H__
#include <memory>
#include <vector>
#include "boost/log/trivial.hpp"

enum ENTITY_TYPE
{
    ET_USER,
    ET_NPC,
    ET_ITEM,
};

// Block Size
struct BlockSize
{
    BlockSize() : row(0), col(0) {}
    BlockSize(int r, int c) : row(r), col(c) {}

    friend std::ostream& operator<<(std::ostream& os, BlockSize& b);

    int row;
    int col;
};

typedef size_t  ENTITY_ID;
typedef std::vector<ENTITY_ID>  ENTITY_ID_VEC;

class iGameEntity;
typedef std::shared_ptr<iGameEntity>    ENTITY_SP;

struct MapPos
{
    MapPos() : x(0), y(0) {}
    MapPos(float _x, float _y) : x(_x), y(_y) {}

    friend std::ostream& operator<<(std::ostream& os, MapPos& b);

    float x;
    float y;
};

struct MoveResult
{
    MoveResult(bool ret) : result(ret) {}

    friend std::ostream& operator<<(std::ostream& os, MoveResult& b);

    bool result;
    std::vector<ENTITY_ID>  entities;   // 周边的对象
};

class GameUser;
typedef std::shared_ptr<GameUser> GAMEUSER_SP;

#endif // !__GAME_COMMONTYPE_H__
