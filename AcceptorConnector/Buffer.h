#pragma once
#include "utility.h"
#include <vector>

class Buffer
    : public noncopyable
{
public:
    Buffer();
    ~Buffer();

private:
    const int m_size;
    int m_readIndex;
    int m_writeInex;
    std::vector<char>   m_buffer;
};

