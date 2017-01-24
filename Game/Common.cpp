#include "CommonType.h"


std::ostream& operator<<(std::ostream& os, BlockSize& b)
{
    os << "(row : " << b.row << " col : " << b.col << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, MapPos& b)
{

    return os;
}

std::ostream& operator<<(std::ostream& os, MoveResult& b)
{

    return os;
}

