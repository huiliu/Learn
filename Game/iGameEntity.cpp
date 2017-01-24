#include "iGameEntity.h"

iGameEntity::~iGameEntity()
{
}

void iGameEntity::SetId(ENTITY_ID id)
{
    m_Id = id;
}

void iGameEntity::SetPost(const MapPos & pos)
{
    m_Pos = pos;
}
