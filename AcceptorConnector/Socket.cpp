#include "common.h"
#include "Socket.h"
#include "InetAddress.h"


int Socket::createSocket()
{
    int fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (INVALID_SOCKET != fd)
    {
        return fd;
    }

    int errcode = WSAGetLastError();
    switch (errcode)
    {
    case WSANOTINITIALISED:
    case WSAENETDOWN:
    case WSAEACCES:
    case WSAEAFNOSUPPORT:
    case WSAEMFILE:     // too many socket
    case WSAEINVAL:
    case WSAEINVALIDPROVIDER:
    case WSAEINVALIDPROCTABLE:
    case WSAENOBUFS:
    case WSAEPROTONOSUPPORT:
    case WSAEPROTOTYPE:
    case WSAEPROVIDERFAILEDINIT:
    case WSAESOCKTNOSUPPORT:
        assert(false);
        break;
    default:
        break;
    }

    return INVALID_SOCKET;
}

Socket::~Socket()
{
    close();
}

void Socket::setKeepAlive(bool on)
{
    setSockOpt(SOL_SOCKET, SO_KEEPALIVE, on);
}

void Socket::setNonBlocking(bool on)
{
}

void Socket::setNoDelay(bool on)
{
    setSockOpt(IPPROTO_TCP, TCP_NODELAY, on);
}

void Socket::setReuseAddr(bool on)
{
    setSockOpt(SOL_SOCKET, SO_REUSEADDR, on);
}

void Socket::setReusePort(bool on)
{
    // doesn't support reuse port
    assert(false);
}

void Socket::setSockOpt(int level, int type, bool val)
{
    // http://man7.org/linux/man-pages/man3/setsockopt.3p.html
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms740476(v=vs.85).aspx
    assert(m_fd > 0);
    char opval = val ? 1 : 0;
    int ret = ::setsockopt(m_fd, level, type, &opval, sizeof(opval));
    if (SOCKET_ERROR != ret)
    {
        return;
    }

    int errcode = WSAGetLastError();
    switch (errcode)
    {
    case WSANOTINITIALISED:
    case WSAENETDOWN:
    case WSAEFAULT:
    case WSAEINPROGRESS:
    case WSAEINVAL:
    case WSAENETRESET:
    case WSAENOPROTOOPT:
    case WSAENOTCONN:
    case WSAENOTSOCK:
    default:
        assert(false);
        break;
    }
}

int Socket::accept(InetAddress& peerAddr)
{
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));

    // http://man7.org/linux/man-pages/man3/accept.3p.html
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms737526(v=vs.85).aspx
    int addrlen = sizeof(struct sockaddr);
    int connfd = ::accept(m_fd, static_cast<struct sockaddr*>((void*)&addr), &addrlen);
    if (INVALID_SOCKET == connfd)
    {
        int errcode = WSAGetLastError();
        switch (errcode)
        {
        case WSANOTINITIALISED:
        case WSAECONNRESET:
        case WSAEFAULT:
        case WSAEINTR:
        case WSAEINPROGRESS:
        case WSAEMFILE:         // too many sockets (file description)
        case WSAENETDOWN:
        case WSAENOBUFS:
        case WSAENOTSOCK:
        case WSAEOPNOTSUPP:
        case WSAEWOULDBLOCK:
            assert(false);
            break;
        default:
            break;
        }

        return INVALID_SOCKET;
    }

    peerAddr.setSockAddr(addr);
    return connfd;
}

void Socket::bindAddress(const InetAddress& addr)
{
    // http://man7.org/linux/man-pages/man3/bind.3p.html
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms737550(v=vs.85).aspx
    int ret = ::bind(m_fd, addr.getSockAddr(), sizeof(struct sockaddr));
    if (SOCKET_ERROR == ret)
    {
        int errcode = WSAGetLastError();
        switch (errcode)
        {
        case WSANOTINITIALISED:
        case WSAENETDOWN:
        case WSAEACCES:
        case WSAEADDRINUSE:     // need SO_REUSEADD
        case WSAEADDRNOTAVAIL:
        case WSAEFAULT:
        case WSAEINPROGRESS:
        case WSAEINVAL:
        case WSAENOBUFS:
        case WSAENOTSOCK:
            assert(false);
            break;
        default:
            assert(false);
            break;
        }
    }
    assert(0 == ret);
}

void Socket::close()
{
    if (INVALID_SOCKET != m_fd)
    {
        ::closesocket(m_fd);
    }
}

void Socket::listen()
{
    // http://man7.org/linux/man-pages/man3/listen.3p.html
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms739168(v=vs.85).aspx
    int ret = ::listen(m_fd, SOMAXCONN);
    if (SOCKET_ERROR != ret)
    {
        return;
    }

    int errcode = WSAGetLastError();
    switch (errcode)
    {
        case WSANOTINITIALISED:
        case WSAENETDOWN:
        case WSAEACCES:
        case WSAEADDRINUSE:     // need SO_REUSEADD
        case WSAEINPROGRESS:
        case WSAEINVAL:
        case WSAEISCONN:
        case WSAEMFILE:
        case WSAENOBUFS:
        case WSAENOTSOCK:
            assert(false);
            break;
    default:
        break;
    }
}

void Socket::shutdownWrite()
{
    // http://man7.org/linux/man-pages/man3/shutdown.3p.html
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms740481(v=vs.85).aspx
    // windows SD_RECEIVE, SD_SEND, SD_BOTH
    // linux SHUT_RD, SHUT_WR, SHUT_RDWR
    int ret = ::shutdown(m_fd, SD_SEND);
    if (SOCKET_ERROR != ret)
    {
        return;
    }

    int errcode = WSAGetLastError();
    switch (errcode)
    {
    case WSAECONNABORTED:
    case WSAECONNRESET:
    case WSAEINPROGRESS:
    case WSAEINVAL:
    case WSAENETDOWN:
    case WSAENOTCONN:
    case WSAENOTSOCK:
    case WSANOTINITIALISED:
    default:
        assert(false);
        break;
    }
}
