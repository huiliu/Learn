#include "Channel.h"
#include "EventLoop.h"
#include "Poller.h"
#include <cassert>    

EventLoop::EventLoop()
    : m_looping(false)
    , m_quit(true)
    , m_poller(new Poller(this))
{
}

EventLoop::~EventLoop()
{
}

void EventLoop::loop()
{
    assert(!m_looping);
    assert(m_quit);

    m_looping = true;
    m_quit = false;

    while (!m_quit)
    {
        m_activeChannels.clear();
        m_poller->poll(-1, &m_activeChannels);

        for (auto& channel : m_activeChannels)
        {
            channel->handleEvent();
        }
    }
}

void EventLoop::quit()
{
    m_quit = true;
}

void EventLoop::updateChannel(Channel* channel)
{
    assert(m_poller);
    m_poller->updateChannel(channel);
}

void EventLoop::unregisterChannel(Channel* channel)
{
    assert(m_poller);
    m_poller->removeChannel(channel);
}
