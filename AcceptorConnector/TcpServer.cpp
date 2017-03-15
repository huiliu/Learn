#include "InetAddress.h"
#include "TcpServer.h"
#include "Socket.h"

void TcpServer::start()
{
    m_acceptor->setNewConnectionCallback(std::bind(&TcpServer::newConnectionCallback,
        this, std::placeholders::_1, std::placeholders::_2));
    m_acceptor->listen();
    m_started = true;
}

void TcpServer::removeConnection(const TcpConnectionPtr& conn)
{
    m_connections.erase(conn->name());
    conn->connectDestroyed();
}

void TcpServer::newConnectionCallback(Socket&& socket, const InetAddress& addr)
{
    char buff[64];
    snprintf(buff, 64, "#%d", ++m_connId);
    std::string connName = m_name + buff;

    // TODO 通过fd取得localaddress
    InetAddress localAddr(80);
    TcpConnectionPtr conn(new TcpConnection(connName, m_loop, std::move(socket), localAddr, addr));
    m_connections[connName] = conn;

    conn->setConnectionCallback(m_connectionCallback);
    conn->setMessageCallback(m_messageCallback);
    conn->setCloseCallback(std::bind(&TcpServer::removeConnection, this, std::placeholders::_1));
    conn->connectEstablished();
}