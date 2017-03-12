#include "InetAddress.h"
#include "Acceptor.h"
#include <cassert>

Acceptor::Acceptor(EventLoop * loop, const InetAddress & listenAddr)
    : m_loop(loop)
    , m_acceptSocket(Socket::createSocket())
    , m_acceptChannel(loop, m_acceptSocket.fd())
    , m_listening(false)
{
    m_acceptSocket.setReuseAddr(true);
    m_acceptSocket.bindAddress(listenAddr);
    m_acceptChannel.setReadCallback(std::bind(&Acceptor::handleRead, this));
}

Acceptor::~Acceptor()
{
}

void Acceptor::listen()
{
    assert(!m_listening);
    m_listening = true;
    m_acceptSocket.listen();
    m_acceptChannel.enableReading();
}

void Acceptor::handleRead()
{
    InetAddress peerAddr(0);
    int connfd = m_acceptSocket.accept(peerAddr);
    if (connfd > 0)
    {
        if (m_newConnectionCallback)
        {
            m_newConnectionCallback(std::move(Socket(connfd)), peerAddr);
        }
    }
}
