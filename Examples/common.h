#pragma once

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <assert.h>

#pragma comment(lib, "Ws2_32.lib")

class WinSock
{
public:
    WinSock()
    {
        // Initialize Winsock
        int iResult = WSAStartup(MAKEWORD(2, 2), &m_data);
        if (iResult != 0) {
            printf("WSAStartup failed with error: %d\n", iResult);
            assert(false);
        }
    }
    ~WinSock()
    {
        WSACleanup();
    }

private:
    WSADATA m_data;
};

