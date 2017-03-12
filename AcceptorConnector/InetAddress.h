#pragma once
#include "common.h"
#include <cstdint>
#include <string>

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

