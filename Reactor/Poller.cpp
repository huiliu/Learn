#include "Channel.h"
#include "Poller.h"
#include <cassert>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <WinSock2.h>

Poller::Poller(EventLoop* loop)
    : m_ownerLoop(loop)
{
}

Poller::~Poller()
{
}

int Poller::poll(int timeoutMs, ChannelList* activeChannels)
{
    int numEvents = ::WSAPoll(&*m_pollfds.begin(), m_pollfds.size(), timeoutMs);
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
        int errcode = WSAGetLastError();
        assert(false);
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
