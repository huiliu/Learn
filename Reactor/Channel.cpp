#include "Channel.h"
#include "EventLoop.h"
#include <cassert>

// pollÊÂ¼þ
// http://man7.org/linux/man-pages/man3/poll.3p.html
// https://msdn.microsoft.com/zh-cn/library/windows/desktop/ms740094(v=vs.85).aspx

#ifdef _MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN;
const int Channel::kWriteEvent = POLLOUT;

#else

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

#endif // _MSC_VER


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
