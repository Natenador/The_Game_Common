/*
 *  Name:   UDP_Socket.hxx
 *  Author: Tom Kroll
 *  Desc:   Wrapper around c-sockets for ease of use.
 *          UDP SOCKET
 */

#ifndef UDP_SOCKET_HXX
#define UDP_SOCKET_HXX

#include "Socket.hxx"

class UDPSocket : Socket {
    public:
        UDPSocket(const std::string ip_address, const unsigned short port);
};

#endif
