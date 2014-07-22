#include "network.hpp"

#include <netdb.h>

namespace network {
  namespace impl {

    const int connect_socket(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
      return connect(sockfd, addr, addrlen);
    };

    const int close_socket(int fd) {
      return close(fd);
    };

    const ssize_t socket_send(int sockfd, const void *buf, size_t len, int flags) {
      return send(sockfd, buf, len, flags);
    };

    const int socket_accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
      return accept(sockfd, addr, addrlen);
    };

    const int create_socket(int domain, int type, int protocol) {
      return socket(domain, type, protocol);
    };

    const int create_socket() {
      return socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    };

    const int bind_socket(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
      return bind(sockfd, addr, addrlen);
    };

    const int socket_listen(int sockfd, int backlog) {
      return listen(sockfd, backlog);
    };

    const ssize_t socket_receive(int sockfd, void *buf, size_t len, int flags) {
      return recv(sockfd, buf, len, flags);
    };

  };

  const uint32_t interpret_address(std::string address) {
    return *(unsigned long *)gethostbyname(address.c_str())->h_addr_list[0];
  }
};
