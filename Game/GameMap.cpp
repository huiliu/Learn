#include "GameMap.h"
#include "Block.h"
#include "EntityManager.h"
#include <cassert>

GameMap::GameMap(ENTITY_ID mid)
    : m_Id(mid)
    , m_MapSize(1000, 1000)
    , m_BlockSize(10, 10)
    , m_RowCount(0)
    , m_ColCount(0)
    , m_BlockVec()
{
    size_t m_RowCount = m_MapSize.row / m_BlockSize.row;
    size_t m_ColCount = m_MapSize.col / m_BlockSize.col;

    MapPos pos;

    for (size_t i = 0; i < m_RowCount; i++)
    {
        for (size_t j = 0; j < m_ColCount; j++)
        {
            pos.x = m_BlockSize.row * i * 1.0f;
            pos.y = m_BlockSize.col * j * 1.0f;
            m_BlockVec.push_back(Block(pos, m_BlockSize));
        }
    }
}

GameMap::~GameMap()
{
}

int GameMap::Init()
{
    return 0;
}

int GameMap::Fini()
{
    return 0;
}

bool GameMap::LoadData()
{
    return false;
}

MoveResult GameMap::EnterMap(ENTITY_ID id, MapPos dest)
{
    MoveResult ret(false);

    ENTITY_SP spEntity = EntityManager::GetInstance()->FindEntity(id);
    if (spEntity)
    {
        return ret;
    }

    ret.result = true;

    size_t bid = GetBlockIdByPos(dest);
    m_BlockVec[bid].Attach(id);

    ret.entities = GetBroadcastEntities(dest);

    BOOST_LOG_TRIVIAL(info) << id << " enter world!";
    return ret;
}

MoveResult GameMap::LeaveMap(ENTITY_ID id, MapPos dest)
{
    MoveResult result(false);

    ENTITY_SP spEntity = EntityManager::GetInstance()->FindEntity(id);
    if (!spEntity)
    {
        return result;
    }

    MapPos pos = spEntity->GetPos();

    result.result = true;
    result.entities = GetBroadcastEntities(pos);

    BOOST_LOG_TRIVIAL(info) << id << " leave world!";
    return result;
}

MoveResult GameMap::MoveTo(ENTITY_ID id, int iSpeed, MapPos dest)
{
    BOOST_LOG_TRIVIAL(info) << "Start Move " << id;
    MoveResult result(false);

    // 检查是否可以达到dest
    if (!CanArrived(id, dest))
    {
        return result;
    }

    ENTITY_SP spEntity = EntityManager::GetInstance()->FindEntity(id);
    assert(spEntity);

    result.entities = GetBroadcastEntities(dest);
    ENTITY_ID_VEC entities = GetBroadcastEntities(spEntity->GetPos());

    result.entities.insert(result.entities.end(), entities.begin(), entities.end());
    
    BOOST_LOG_TRIVIAL(info) << "Entity ID: " << id << " Speed: " << iSpeed
        << "; From: " << spEntity->GetPos().x << "/" << spEntity->GetPos().y
        << "; Dest: " << dest.x << " / " << dest.y;

    return result;
}

size_t GameMap::GetBlockIdByPos(const MapPos & pos)
{
    int row = static_cast<int>(pos.x) / m_BlockSize.row;
    int col = static_cast<int>(pos.y) / m_BlockSize.col;

    return m_RowCount * row + col;
}

ENTITY_ID_VEC GameMap::GetBroadcastEntities(const MapPos & pos)
{
    ENTITY_ID_VEC vecEntities;
    int row = static_cast<int>(pos.x) / m_BlockSize.row;
    int col = static_cast<int>(pos.y) / m_BlockSize.col;

    int rmin = row - 1 > 0 ? row - 1 : 0;
    int rmax = row + 1 < m_RowCount ? row - 1 : m_RowCount;

    int cmin = col - 1 > 0 ? col - 1 : 0;
    int cmax = col + 1 < m_ColCount ? col - 1 : m_ColCount;

    for (int i = rmin; i < rmax; i++)
    {
        for (int j = cmin; j < cmax; j++)
        {
            int id = m_RowCount * i + j;
            ENTITY_ID_VEC temp(m_BlockVec.at(id).GetAllEntities());
            vecEntities.insert(vecEntities.end(), temp.begin(), temp.end());
        }

    }

    return vecEntities;
}

bool GameMap::CanArrived(ENTITY_ID id, const MapPos & pos)
{
    ENTITY_SP spEntity = EntityManager::GetInstance()->FindEntity(id);

    assert(nullptr != spEntity);
    if (nullptr == spEntity)
    {
        return false;
    }

    // 暂时没有检查
    return true;
}
