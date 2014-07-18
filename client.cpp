#include "client.hpp"

void client::add_neighbor(std::string ip_address, unsigned int socket) {
  comm_sockets.push_back(network::socket::connected(ip_address, socket));
}

void client::send(std::string message) {
  for (auto s : comm_sockets) { s.send(message); }
}

std::string client::receive() {
  std::string message = "";
  for (auto s : comm_sockets) {
    message = s.receive(1024);
    if (message != "") return message;
  }
  return message;
}

void client::accept() {
  auto s = interface.accept();
  comm_sockets.push_back(s);
}
