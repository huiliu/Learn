#pragma once

#include <vector>
#include <map>

class Channel;
class EventLoop;
struct pollfd;

class Poller
{
    typedef std::vector<Channel*>   ChannelList;

public:
    Poller(EventLoop* loop);
    ~Poller();

    int poll(int timeoutMs, ChannelList* activeChannels);
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);

private:
    void fillActiveChannels(int numEvents, ChannelList* activeChannels);

private:
    typedef std::vector<struct pollfd>  PollFdList;
    typedef std::map<int, Channel*>     ChannelMap;

    EventLoop*  m_ownerLoop;
    PollFdList  m_pollfds;
    ChannelMap  m_channels;
};

