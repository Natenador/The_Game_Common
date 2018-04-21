/*
 *  Name:   TCP_Socket.hxx
 *  Author: Tom Kroll
 *  Desc:   Wrapper around c-sockets for ease of use.
 *          TCP SOCKET Implementation.
 */

#ifndef TCP_SOCKET_HXX
#define TCP_SOCKET_HXX

#include "Socket.hxx"

class TCPSocket : Socket {
    public:
        TCPSocket(const std::string ip_address, const unsigned short port);
        void connect_to_server(const std::string server_addr, const unsigned short serv_port);
        void connect_to_server();
};

#endif
