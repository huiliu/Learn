#include "../AcceptorConnector/Acceptor.h"
#include "../AcceptorConnector/InetAddress.h"
#include "../AcceptorConnector/TcpServer.h"
#include "../Reactor/EventLoop.h"
#include "../Reactor/Poller.h"
#include "common.h"
#include <iostream>

void
onConnection(const TcpConnectionPtr& conn)
{
    if (conn->connected())
    {
        printf("onConnection: new connection %s\n", conn->name().data());
    }
    else
    {
        printf("onConnection: connection %s is down!\n", conn->name().data());
    }
}

void
onMessage(const TcpConnectionPtr& conn, const char* buff, int size)
{
    printf("%s connection received message %s\n", conn->name().data(), buff);
}

int main()
{
    WinSock winSock;

    EventLoop loop;
    Poller poll(&loop);
    TcpServer server("server", &loop, InetAddress(8090));

    server.setConnectionCallback(onConnection);
    server.setMessageCallback(onMessage);
    server.start();

    loop.loop();

    return 0;
}

