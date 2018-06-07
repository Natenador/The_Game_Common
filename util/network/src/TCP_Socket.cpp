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
    connected = false;
}


void TCPSocket::connect_to_server() {
    if(connect(m_sock, (struct sockaddr *)&m_remote_addr, sizeof(m_remote_addr)) < 0) {
        throw SocketException("Error attempting to connect to the remote address.");
    }
    connected = true;
}

void TCPSocket::connect_to_server(const std::string server_addr, const unsigned short serv_port) {
    set_remote(server_addr, serv_port);
    connect_to_server();
}

void TCPSocket::send_message(const char buffer[], const int data_bytes) {
    // TODO: change const char buffer[] to some variation of smart pointer?
    if(!connected) {
        throw SocketException("TCP message attempted to be sent before a connection established.");
    }
    Socket::send_message(buffer, data_bytes);
}

int TCPSocket::receive_message(char buffer[], const int buffer_size) {
    if(!connected) {
        throw SocketException("Attempted to receive a TCP message before a connection established.");
    }
    return Socket::receive_message(buffer, buffer_size);
}
