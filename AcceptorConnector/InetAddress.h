#pragma once
#include <cstdint>
#include <string>

#ifdef _MSC_VER
#else
#include <netinet/in.h>
#endif // _MSC_VER

#ifdef _MSC_VER
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <winsock2.h>
#else
// non windows
#include <netinet/in.h>
#endif // _MSC_VER

class InetAddress
{
public:
    explicit InetAddress(uint16_t port, bool loopbackonly = false, bool ipv6 = false);
    InetAddress(const std::string& ip, uint16_t port, bool ipv6 = false);

    explicit InetAddress(const struct sockaddr_in& addr) : m_addr(addr) {}

    ~InetAddress();

public:
    short family() const;
    std::string ip() const;
    uint16_t    port() const;
    const struct sockaddr* getSockAddr() const;
    void setSockAddr(const struct sockaddr_in& addr) { m_addr = addr; }

private:
    struct sockaddr_in  m_addr;
};

