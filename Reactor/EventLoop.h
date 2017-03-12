#pragma once
#include <memory>
#include <vector>

class Channel;
class Poller;

class EventLoop
{
public:
    EventLoop();
    ~EventLoop();

    void loop();
    void quit();
    void updateChannel(Channel* channel);

private:
    typedef std::vector<Channel*>   ChannelVector;

    bool m_looping;
    bool m_quit;
    std::shared_ptr<Poller> m_poller;
    ChannelVector   m_activeChannels;
};

