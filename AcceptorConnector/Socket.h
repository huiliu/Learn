#pragma once

class InetAddress;

class Socket
{
public:
    static int createSocket();

public:
    explicit Socket(int fd) : m_fd(fd) {}
    ~Socket();

    Socket(const Socket&) = delete;
    Socket& operator=(const Socket&) = delete;

    Socket(Socket&& other);

public:
    int fd() const { return m_fd; }

public:
    void setKeepAlive(bool on);
    void setNonBlocking(bool on);
    void setNoDelay(bool on);
    void setReuseAddr(bool on);
    void setReusePort(bool on);

private:
    void setSockOpt(int level, int type, bool val);

public:
    int  accept(InetAddress& peerAddr);
    void bindAddress(const InetAddress& addr);
    void close();
    void listen();
    void shutdownWrite();

private:
    int m_fd;
};

