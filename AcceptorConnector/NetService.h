#pragma once
#include "common.h"
#include <string>

class EventLoop;

class NetService
{
public:
    NetService(EventLoop* loop, const std::string& ip, int port);
    ~NetService();

private:
    EventLoop*  m_loop;
    std::string m_ip;
    int     m_port;
};

