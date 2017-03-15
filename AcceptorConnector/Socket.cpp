#include "Socket.h"
#include "InetAddress.h"
#include <cassert>

#ifdef _MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>

// windows SD_RECEIVE, SD_SEND, SD_BOTH
// linux SHUT_RD, SHUT_WR, SHUT_RDWR
#define SHUT_RD     SD_RECEIVE
#define SHUT_WR     SD_SEND
#define SHUT_RDWR   SD_BOTH

#else
// non-windows
#include <sys/socket.h>
#define INVALID_SOCKET  -1
#define SOCKET_ERROR    -1
#endif // _MSC_VER


static void socket_error(int errcode)
{
    switch (errcode)
    {
    // socket
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
}


int Socket::createSocket()
{
#ifdef _MSC_VER
    int fd = ::socket(AF_INET, SOCK_STREAM, 0);
#else
    int fd = ::socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, 0);
#endif // _MSC_VER

    if (INVALID_SOCKET != fd)
    {
        return fd;
    }

#ifdef _MSC_VER
    int errcode = WSAGetLastError();
#else
    int errcode = errno;
#endif // _MSC_VER

    socket_error(errcode);

    return INVALID_SOCKET;
}

Socket::~Socket()
{
    close();
}

Socket::Socket(Socket&& other)
    : m_fd(other.m_fd)
{
    other.m_fd = INVALID_SOCKET;
}

void Socket::setKeepAlive(bool on)
{
    setSockOpt(SOL_SOCKET, SO_KEEPALIVE, on);
}

void Socket::setNonBlocking(bool on)
{
    // TODO: 错误处理
#ifdef _MSC_VER
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms738573(v=vs.85).aspx
    // FIONBIO, FIONREAD, FIOCATMARK
    u_long argp = on ? 1 : 0;
    if (ioctlsocket(m_fd, FIONBIO, &argp) == SOCKET_ERROR)
    {
        int errcode = WSAGetLastError();
        socket_error(errcode);
        assert(false);
    }
#else
    // http://man7.org/linux/man-pages/man2/fcntl.2.html
    int flags = fcntl(m_fd, F_GETFL);
    if (-1 == flags)
    {
        int errcode = errno;
        socket_error(errcode);
        assert(false);
        return;
    }
    flags |= O_NONBLOCK;
    if (fcntl(m_fd, F_SETFL, flags) == -1)
    {
        int errcode = errno;
        socket_error(errcode);
        assert(false);
        return;
    }

#endif // _MSC_VER
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

#ifdef _MSC_VER
    int errcode = WSAGetLastError();
#else
    int errcode = errno;
#endif // _MSC_VER

    socket_error(errcode);
    return;

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
    if (INVALID_SOCKET != connfd)
    {
        peerAddr.setSockAddr(addr);
        return connfd;
    }

#ifdef _MSC_VER
    int errcode = WSAGetLastError();
#else
    int errcode = errno;
#endif // _MSC_VER

    socket_error(errcode);
    return INVALID_SOCKET;

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

void Socket::bindAddress(const InetAddress& addr)
{
    // http://man7.org/linux/man-pages/man3/bind.3p.html
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms737550(v=vs.85).aspx
    int ret = ::bind(m_fd, addr.getSockAddr(), sizeof(struct sockaddr));
    if (SOCKET_ERROR != ret)
    {
        return;
    }

#ifdef _MSC_VER
    int errcode = WSAGetLastError();
#else
    int errcode = errno;
#endif // _MSC_VER

    socket_error(errcode);
    return;

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

void Socket::close()
{
    if (INVALID_SOCKET != m_fd)
    {
#ifdef _MSC_VER
        ::closesocket(m_fd);
#else
        close(m_fd);
#endif // _MSC_VER
    }
}

void Socket::listen()
{
    // TODO: 错误处理
    // http://man7.org/linux/man-pages/man3/listen.3p.html
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms739168(v=vs.85).aspx
    int ret = ::listen(m_fd, SOMAXCONN);
    if (SOCKET_ERROR != ret)
    {
        return;
    }

#ifdef _MSC_VER
    int errcode = WSAGetLastError();
#else
    int errcode = errno;
#endif // _MSC_VER

    socket_error(errcode);
    return;

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
    // TODO: 错误处理
    // http://man7.org/linux/man-pages/man3/shutdown.3p.html
    // https://msdn.microsoft.com/en-us/library/windows/desktop/ms740481(v=vs.85).aspx
    // windows SD_RECEIVE, SD_SEND, SD_BOTH
    // linux SHUT_RD, SHUT_WR, SHUT_RDWR
    int ret = ::shutdown(m_fd, SHUT_WR);
    if (SOCKET_ERROR != ret)
    {
        return;
    }

#ifdef _MSC_VER
    int errcode = WSAGetLastError();
#else
    int errcode = errno;
#endif // _MSC_VER

    socket_error(errcode);
    return;

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
