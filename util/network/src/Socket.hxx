/*
 *  Name:   Socket.hxx
 *  Author: Tom Kroll
 *  Desc:   Wrapper around c-sockets for ease of use.
 */


#ifndef SOCKET_HXX
#define SOCKET_HXX

#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

#include <stdexcept>

class SocketException : public std::runtime_error {
    public:
        SocketException(std::string const& error) : std::runtime_error(error) { };
};

class Socket {
    public:
        Socket(const std::string ip_address, const unsigned short port);
        virtual ~Socket(); // Allow children to declare their own destructors.
        void set_remote(const std::string ip_address, const unsigned short port);
        void bind_sock();
    protected:
        int m_sock;
        struct sockaddr_in m_addr;
        struct sockaddr_in m_remote_addr;
};

#endif
