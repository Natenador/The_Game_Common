/*
 *  Name:   Socket.cpp
 *  Author: Tom Kroll
 *  Desc:   Wrapper around c-sockets for ease of use.
 */
// ################################################################################################
// UDP SOCKET IMPLEMENTATION
// ################################################################################################

#include "UDP_Socket.hxx"

UDPSocket::UDPSocket(const std::string ip_address, const unsigned short port) : Socket(ip_address, port) {
    if((m_sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        throw SocketException("Unable to allocate UDP Socket.");
    }
}

