#pragma once
#include "Acceptor.h"
#include "TcpConnection.h"
#include <functional>
#include <map>
#include <string>

class Acceptor;
class EventLoop;
class InetAddress;
class Socket;
class TcpConnection;

class TcpServer
{
public:
    typedef std::function<void(const TcpConnectionPtr&)>    ConnectionCallback;
    typedef std::function<void(const TcpConnectionPtr&, const char*, int)>     MessageCallback;

public:
    TcpServer(const std::string& name, EventLoop* loop, const InetAddress& addr)
        : m_loop(loop)
        , m_acceptor(new Acceptor(loop, addr))
        , m_started(false)
        , m_name(name)
        , m_connId(0)
    {
    }

    ~TcpServer() {}

public:
    void start();
    void setConnectionCallback(const ConnectionCallback& cb) { m_connectionCallback = cb; }
    void setMessageCallback(const MessageCallback& cb) { m_messageCallback = cb; }
    void removeConnection(const TcpConnectionPtr& conn);

private:
    void newConnectionCallback(Socket&& socket, const InetAddress& addr);

private:
    typedef std::map<std::string, TcpConnectionPtr>   ConnectionMap;

    EventLoop*  m_loop;
    Acceptor*   m_acceptor;
    bool        m_started;
    std::string m_name;
    int         m_connId;
    ConnectionMap m_connections;
    ConnectionCallback  m_connectionCallback;
    MessageCallback     m_messageCallback;
};

