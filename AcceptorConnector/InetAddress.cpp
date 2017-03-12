#include "InetAddress.h"

InetAddress::InetAddress(uint16_t port, bool loopbackonly, bool /*ipv6*/)
{
    memset(&m_addr, 0, sizeof(m_addr));
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    m_addr.sin_addr.s_addr = loopbackonly ? INADDR_LOOPBACK : INADDR_ANY;
}

InetAddress::InetAddress(const std::string & ip, uint16_t port, bool /*ipv6*/)
{
    memset(&m_addr, 0, sizeof(m_addr));
    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);
    if (::inet_pton(AF_INET, ip.data(), &m_addr.sin_addr) <= 0)
    {
        assert(false);
    }
}

InetAddress::~InetAddress()
{
}

short InetAddress::family() const
{
    return m_addr.sin_family;
}

std::string InetAddress::ip() const
{
    return std::string();
}

uint16_t InetAddress::port() const
{
    return ntohs(m_addr.sin_port);
}

const sockaddr* InetAddress::getSockAddr() const
{
    return static_cast<struct sockaddr*>((void*)&m_addr);
}
