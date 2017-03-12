#pragma once
#include "Socket.h"
#include "../Reactor/Channel.h"

#include <functional>

class EventLoop;
class Socket;
class InetAddress;

class Acceptor
{
public:
    typedef std::function<void(Socket&& s, const InetAddress& addr)>   NewConnectionCallback;

public:
    Acceptor(EventLoop* loop, const InetAddress& listenAddr);
    ~Acceptor();

    bool listening() const { return m_listening; }
    void listen();
    void setNewConnectionCallback(const NewConnectionCallback& cb) { m_newConnectionCallback = cb; }

private:
    void handleRead();

private:
    EventLoop*  m_loop;
    Socket      m_acceptSocket;
    Channel     m_acceptChannel;
    bool        m_listening;
    NewConnectionCallback   m_newConnectionCallback;
};

