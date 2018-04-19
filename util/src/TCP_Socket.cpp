/*
 *  Name:   TCP_Socket.cpp
 *  Author: Tom Kroll
 *  Desc:   Wrapper around c-sockets for ease of use.
 */
// ################################################################################################
// TCP SOCKET IMPLEMENTATION
// ################################################################################################

#include "TCP_Socket.hxx"

TCPSocket::TCPSocket(const std::string ip_address, const unsigned short port) : Socket(ip_address, port) {
    if((m_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        throw SocketException("Unable to allocate TCP Socket.");
    }
}
