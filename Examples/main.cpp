#include "../AcceptorConnector/Acceptor.h"
#include "../AcceptorConnector/InetAddress.h"
#include "../Reactor/EventLoop.h"
#include "../Reactor/Poller.h"
#include "common.h"
#include <iostream>

void
newConnectionCallback(Socket&& socket, const InetAddress& peerAddr)
{
    if (socket.fd() <= 0)
    {
        std::cout << "invalid socket!" << std::endl;
        return;
    }

    std::cout << "connection come from " << peerAddr.ip() << ":" << peerAddr.port() << std::endl;
    socket.close();
}

int main()
{
    WinSock winSock;

    EventLoop loop;
    Poller poll(&loop);
    Acceptor acceptor(&loop, InetAddress(8090));

    acceptor.setNewConnectionCallback(newConnectionCallback);
    acceptor.listen();

    loop.loop();

    return 0;
}

