//
// 
//
#pragma once

#include <functional>

class EventLoop;

class Channel
{
public:
    typedef std::function<void()>   EventCallback;

public:
    Channel(EventLoop* loop, int fd);
    ~Channel();

    void handleEvent();

    void setReadCallback(const EventCallback& cb)
    {
        m_readCallback = cb;
    }

    void setWriteCallback(const EventCallback& cb)
    {
        m_writeCallback = cb;
    }

    void setErrorCallback(const EventCallback& cb)
    {
        m_errorCallback = cb;
    }

    int fd() const { return m_fd; }
    int events() const { return m_events; }
    void set_revents(int revt) { m_revents = revt; }
    bool isNoneEvent() const { return kNoneEvent == m_events; }

    void enableReading() { m_events |= kReadEvent; update(); }
    void enableWriting() { m_events |= kWriteEvent; update(); }
    void disableWriting() { m_events &= ~kWriteEvent; update(); }
    void disableAll() { m_events = kNoneEvent; update(); }

    int index() const { return m_index; }
    void set_index(int idx) { m_index = idx; }

private:
    void update();

private:
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

private:
    int m_fd;
    int m_events;
    int m_revents;
    int m_index;
    EventLoop*   m_loop;

    EventCallback   m_readCallback;
    EventCallback   m_writeCallback;
    EventCallback   m_errorCallback;
};

