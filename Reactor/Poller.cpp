#include "Channel.h"
#include "Poller.h"
#include <cassert>
#include <cerrno>

#ifdef _MSC_VER

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>

#define Poll    WSAPoll

#else

#define Poll    poll

#endif // _MSC_VER


Poller::Poller(EventLoop* loop)
    : m_ownerLoop(loop)
{
}

Poller::~Poller()
{
}

// 

int Poller::poll(int timeoutMs, ChannelList* activeChannels)
{
    // TODO: ´íÎó´¦Àí
    // http://man7.org/linux/man-pages/man3/poll.3p.html
    // https://msdn.microsoft.com/zh-cn/library/windows/desktop/ms741669(v=vs.85).aspx
    int numEvents = ::Poll(&*m_pollfds.begin(), m_pollfds.size(), timeoutMs);
    if (numEvents > 0)
    {
        fillActiveChannels(numEvents, activeChannels);
        return numEvents;
    }
    else if (0 == numEvents)
    {
        // nothing happens;
    }
    else
    {
#ifdef _MSC_VER
        int errcode = WSAGetLastError();
        assert(false);
#else
        int errcode = errno;
        assert(false);
#endif // _MSC_VER

    }
    return numEvents;
}

void Poller::updateChannel(Channel* channel)
{
    if (channel->index() < 0)
    {
        // channel not in m_channels
        // not thread safe

        struct pollfd pfd;

        pfd.fd = channel->fd();
        pfd.events = channel->events();
        pfd.revents = 0;
        m_pollfds.push_back(pfd);

        int idx = m_pollfds.size() - 1;
        channel->set_index(idx);
        m_channels[pfd.fd] = channel;
    }
    else
    {
        // update existed channel
        int idx = channel->index();
        struct pollfd& pfd = m_pollfds[idx];
        assert(channel->fd() == pfd.fd || pfd.fd == -1);
        pfd.events = channel->events();
        pfd.revents = 0;

        if (channel->isNoneEvent())
        {
            // ignore this pollfd
            pfd.fd = -1;
        }
    }
}

void Poller::removeChannel(Channel* channel)
{
    m_channels.erase(channel->fd());

    int idx = channel->index();
    if (idx == m_pollfds.size() - 1)
    {
        m_pollfds.pop_back();
        return;
    }

    std::swap(m_pollfds.begin() + idx, m_pollfds.end() - 1);
    struct pollfd& tail = m_pollfds[idx];
    m_pollfds.pop_back();
    m_channels[tail.fd]->set_index(idx);
}

void Poller::fillActiveChannels(int numEvents, ChannelList* activeChannels)
{
    for (const auto& pfd : m_pollfds)
    {
        if (pfd.revents > 0)
        {
            // events has been trigger
            auto it = m_channels.find(pfd.fd);
            assert(m_channels.end() != it);
            auto* channel = it->second;
            assert(pfd.fd == channel->fd());

            channel->set_revents(pfd.revents);
            activeChannels->push_back(channel);

            --numEvents;
        }

        if (numEvents <= 0)
        {
            break;
        }
    }
}
