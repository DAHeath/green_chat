#include "socket.hpp"

#include <netdb.h>

namespace network {

  socket socket::bound(const int port, const int queueSize) {
    int s = network::impl::create_socket();
    impl::socket_address a = build_address(port);
    impl::bind_socket(s, (struct sockaddr*)&a, sizeof(a));
    impl::socket_listen(s, queueSize);
    return socket(s);
  };

  impl::socket_address socket::build_address(const int port) {
    impl::socket_address addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(port);
    return addr;
  }

  socket socket::connected(const uint32_t ip_address, const int port) {
    int s = impl::create_socket();
    impl::socket_address a = build_address(ip_address, port);
    impl::connect_socket(s, (struct sockaddr*)&a, sizeof(a));
    return socket(s);
  }

  impl::socket_address socket::build_address(
      const uint32_t ip_address, const int port) {
    impl::socket_address addr;
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = ip_address;
    addr.sin_port = htons(port);
    return addr;
  }

  void socket::send(const std::string message) const {
    impl::socket_send(s, message.c_str(), message.length(), 0);
  }

  std::string socket::receive(const unsigned int length) const {
    if (length <= 0) return "";
    char buffer[length+1];
    int len = impl::socket_receive(s, buffer, length, 0);
    if (len <= 0) return "";

    buffer[len] = '\0';
    std::string message;
    message.append(buffer, len);
    return message;
  }

  socket socket::accept() const {
    impl::socket_address addr;
    unsigned int len = sizeof(addr);
    int new_s = impl::socket_accept(s, (struct sockaddr*)&addr, &len);
    return socket(new_s);
  }

  void socket::close() const {
    impl::close_socket(s);
  }

};
