#pragma once
#include "../Reactor/Channel.h"
#include "Socket.h"
#include "InetAddress.h"
#include <functional>
#include <memory>
#include <string>

class Channel;
class EventLoop;
class InetAddress;
class Socket;
class TcpConnection;

typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;

class TcpConnection
    : public std::enable_shared_from_this<TcpConnection>
{
public:
    enum State
    {
        CONNECTING,
        CONNECTED,
        DISCONNECT,
    };

    typedef std::function<void(const TcpConnectionPtr&, const char*, int)>     MessageCallback;
    typedef std::function<void(const TcpConnectionPtr&)>    CloseCallback;
    typedef std::function<void(const TcpConnectionPtr&)>    ConnectionCallback;

public:
    TcpConnection(const std::string& name, EventLoop* loop, Socket&& socket, const InetAddress& localAddr, const InetAddress& peerAddr);
    ~TcpConnection();

    const std::string& name() { return m_name; }

public:
    bool connected() const { return m_state == CONNECTED; }

public:
    void setConnectionCallback(const ConnectionCallback& cb) { m_connectionCallback = cb; }
    void setMessageCallback(const MessageCallback& cb) { m_messageCallback = cb; }
    void setCloseCallback(const CloseCallback& cb) { m_closeCallback = cb; }
    void connectEstablished();
    void connectDestroyed();

private:
    void handleRead();
    void handleWrite();
    void handleClose();
    void handleError();

private:
    std::string m_name;
    EventLoop* m_loop;
    Socket  m_socket;
    InetAddress m_localAddress;
    InetAddress m_peerAddress;
    State   m_state;
    Channel m_channel;
    ConnectionCallback m_connectionCallback;
    MessageCallback m_messageCallback;
    CloseCallback   m_closeCallback;
};

