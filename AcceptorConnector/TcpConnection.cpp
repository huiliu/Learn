#include "../Reactor/EventLoop.h"
#include "TcpConnection.h"

TcpConnection::TcpConnection(const std::string& name, EventLoop* loop, Socket&& socket,
    const InetAddress& localAddr, const InetAddress& peerAddr)
    : m_name(name)
    , m_loop(loop)
    , m_socket(std::move(socket))
    , m_localAddress(localAddr)
    , m_peerAddress(peerAddr)
    , m_state(CONNECTING)
    , m_channel(m_loop, m_socket.fd())
{
}

TcpConnection::~TcpConnection()
{
}

void TcpConnection::connectEstablished()
{
    m_state = CONNECTED;

    m_channel.setReadCallback(std::bind(&TcpConnection::handleRead, this));
    m_channel.setWriteCallback(std::bind(&TcpConnection::handleWrite, this));
    m_channel.setErrorCallback(std::bind(&TcpConnection::handleError, this));
    m_channel.enableReading();

    m_loop->updateChannel(&m_channel);
}

void TcpConnection::connectDestroyed()
{
    m_state = DISCONNECT;
    m_channel.disableAll();
    m_loop->unregisterChannel(&m_channel);
}

void TcpConnection::handleRead()
{
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms740121(v=vs.85).aspx
    char buff[65536] = {};
    int ret = ::recv(m_socket.fd(), buff, sizeof(buff), 0);
    if (ret > 0)
    {
        m_messageCallback(shared_from_this(), buff, ret);
    }
    else if (0 == ret)
    {
        handleClose();
    }
    else
    {
        handleError();
    }
}

void TcpConnection::handleWrite()
{
}

void TcpConnection::handleClose()
{
    m_channel.disableAll();
    m_closeCallback(shared_from_this());
}

void TcpConnection::handleError()
{
#ifdef _MSC_VER
    int errcode = WSAGetLastError();
#else
    int errcode = errno;
#endif // _MSC_VER

    printf("read data error. errocode:%d\n", errcode);
    connectDestroyed();
    // TODO:  ‰≥ˆ¥ÌŒÛ‘≠“Ú
}
