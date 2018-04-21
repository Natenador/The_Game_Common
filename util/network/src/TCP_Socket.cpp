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


void TCPSocket::connect_to_server() {
    if(connect(m_sock, (struct sockaddr *)&m_remote_addr, sizeof(m_remote_addr)) < 0) {
        throw SocketException("Error attempting to connect to the remote address.");
    }
}

void TCPSocket::connect_to_server(const std::string server_addr, const unsigned short serv_port) {
    set_remote(server_addr, serv_port);
    connect_to_server();
}
