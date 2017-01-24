#ifndef __GAME_IENTITY_H__
#define __GAME_IENTITY_H__
#include "CommonType.h"

class iGameEntity
{
public:
    virtual ~iGameEntity();

public:
    virtual int Init() = 0;
    virtual int Fini() = 0;

public:
    void   SetId(ENTITY_ID id);
    ENTITY_ID GetId() const { return m_Id; }

    void   SetPost(const MapPos& pos);
    MapPos GetPos() const { return m_Pos; }

private:
    ENTITY_ID m_Id;
    MapPos m_Pos;
};

#endif
