#include "Channel.h"
#include "EventLoop.h"
#include <cassert>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop * loop, int fd)
    : m_fd(fd)
    , m_events(0)
    , m_revents(0)
    , m_index(-1)
    , m_loop(loop)
{
}

Channel::~Channel()
{
}

void Channel::handleEvent()
{
    if (m_revents & (POLLERR | POLLNVAL))
    {
        if (m_errorCallback) m_errorCallback();
    }

    if (m_revents & (POLLIN | POLLPRI | POLLHUP))
    {
        if (m_readCallback) m_readCallback();
    }

    if (m_revents & POLLOUT)
    {
        if (m_writeCallback) m_writeCallback();
    }
}

void Channel::update()
{
    assert(nullptr != m_loop);
    m_loop->updateChannel(this);
}
