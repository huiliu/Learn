#include "Block.h"

Block::Block(const MapPos & pos, BlockSize & sz)
    : m_Pos(pos)
    , m_BlockSize(sz)
    , m_Entities()
{
}

Block::~Block()
{
    m_Entities.clear();
}

bool Block::Attach(ENTITY_ID id)
{
    bool ret = false;
    if (!IsInBlock(id))
    {
        m_Entities[id] = true;
        ret = false;
    }

    return ret;
}

bool Block::Detach(ENTITY_ID id)
{
    m_Entities.erase(id);
    return true;
}

ENTITY_ID_VEC Block::GetAllEntities() const
{
    ENTITY_ID_VEC vec;
    for (auto& record : m_Entities)
        vec.push_back(record.first);

    return vec;
}

bool Block::IsInBlock(ENTITY_ID id)
{
    return m_Entities.find(id) == m_Entities.cend();
}
