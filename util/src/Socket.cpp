/*
 *  Name:   Socket.cpp
 *  Author: Tom Kroll
 *  Desc:   Wrapper around c-sockets for ease of use.
 */

#include "Socket.hxx"

#ifdef __linux__
#include <arpa/inet.h>
#elif defined(_WIN32)
#include <Ws2tcpip.h>
#endif

Socket::Socket(const std::string ip_address, const unsigned short port) {
    m_addr.sin_family = AF_INET;
#ifdef __linux__
    if(inet_pton(AF_INET, ip_address.c_str(), &m_addr.sin_addr) <= 0) {
        throw SocketException("Invalid IP Address.");
    }
#elif defined (_WIN32)
    if(InetPton(AF_INET, ip_address, &m_addr.sin_addr) <= 0) { // Needs to be tested.
        throw SocketException("Invalid IP Address.");
    }
#endif
    m_addr.sin_port = htons(port);
}

