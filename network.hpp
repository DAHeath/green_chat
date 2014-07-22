#ifndef NETWORK_HPP
#define NETWORK_HPP

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <cstdint>
#include <string>

namespace network {
  namespace impl {

    typedef sockaddr_in socket_address;

    const int     create_socket  (int domain, int type, int protocol);
    const int     create_socket  ();
    const int     close_socket   (int fd);
    const int     connect_socket (int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    const int     bind_socket    (int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    const int     socket_listen  (int sockfd, int backlog);
    const int     socket_accept  (int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    const ssize_t socket_send    (int sockfd, const void *buf, size_t len, int flags);
    const ssize_t socket_receive (int sockfd, void *buf, size_t len, int flags);


  };

  const uint32_t interpret_address(std::string);
};

#endif
