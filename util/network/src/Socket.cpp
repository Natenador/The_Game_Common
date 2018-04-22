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
    m_remote_addr.sin_port = 0;
}

Socket::~Socket() {
    shutdown(m_sock, 2);
}

void Socket::set_remote(const std::string ip_address, const unsigned short port) {
    m_remote_addr.sin_family = AF_INET;
    m_remote_addr.sin_port = htons(port);
#ifdef __linux__
    if(inet_pton(AF_INET, ip_address.c_str(), &m_remote_addr.sin_addr) <= 0) {
        throw SocketException("Invalid IP Address.");
    }
#elif defined (_WIN32)
    if(InetPton(AF_INET, ip_address, &m_addr.sin_addr) <= 0) { // Needs to be tested.
        throw SocketException("Invalid IP Address.");
    }
#endif
}

void Socket::bind_sock() {
    if(bind(m_sock, (struct sockaddr *)&m_addr, sizeof(m_addr)) < 0) {
        throw SocketException("Error binding Socket.");
    }
}


void Socket::send_message(const char buffer[], const int data_bytes) {
    // TODO: change const char buffer[] to some variation of smart pointer?
    char* data_ptr = (char*) &buffer;
    int bytes_to_send = data_bytes;

    while(bytes_to_send > 0) {
        if(bytes_to_send > MAX_BUFFER_SIZE) {
            // IF message too big for the buffer, send it piecemeal.
            send(m_sock, data_ptr, MAX_BUFFER_SIZE, 0);
            bytes_to_send -= MAX_BUFFER_SIZE;
            data_ptr += MAX_BUFFER_SIZE;
        }
        else {
            // If the message (or what remains of the message) is smaller than the buffer
            // send it directly and set bytes_to_send to 0 for loop exit.
            send(m_sock, data_ptr, bytes_to_send, 0);
            bytes_to_send = 0;
        }
    }
}
