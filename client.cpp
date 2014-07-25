#include "client.hpp"
#include "message_types.hpp"

void client::add_neighbor(uint32_t ip_address, unsigned int socket) {
  comm_sockets.push_back(network::socket::connected(ip_address, socket));
}

void client::remove_neighbor(uint32_t ip_address) {

}

void client::send(std::string message) {
  for (auto s : comm_sockets) { s.send(message); }
}

void client::sendtoOne(uint32_t type, socket s) {

}

socket client::getsocketbyaddress(uint32_t ip_address) {

}

std::string client::getnamebyaddress(uint32_t ip_address) {

}

std::string client::receive() {
  std::string message = "";
  for (auto s : comm_sockets) {
    message = s.receive(1024);
    if (message != "") return message;
  }
  return message;
}

std::string client::receiveConnection() {
  std::string message = "";
  for (auto s : couriers) {
    message = s.receive(1024);
    if (message != "") return message;
  }
  return message;
}

void client::accept() {
  auto s = interface.accept();
  couriers.push_back(s);
}

