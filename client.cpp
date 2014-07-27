#include "client.hpp"
#include "message_types.hpp"

void client::add_neighbor(
    uint32_t ip_address,
    std::string name,
    unsigned int socket) {
  network::socket result = network::socket::connected(ip_address, socket);
  comm_sockets.push_back(result);
  addresses.push_back(ip_address);
  names.push_back(name);
}

void client::remove_neighbor(uint32_t ip_address) {
    unsigned int n;
    for (n = 0; n < addresses.size(); n++) {
      if (addresses[n] == ip_address) { break;}
    }
    addresses.erase(addresses.begin() + n);
    network::socket toremove = comm_sockets[n];
    comm_sockets.erase(comm_sockets.begin() + n);
    toremove.close();
    names.erase(names.begin() + n);
}

network::socket client::move_to_comm(uint32_t ip_address, std::string name) {
  network::socket result = couriers[0];
  comm_sockets.push_back(result);
  addresses.push_back(ip_address);
  names.push_back(name);
  couriers.erase(couriers.begin());
  return result;
}

void client::send(std::string message) {
  for (auto s : comm_sockets) { s.send(message); }
}

void client::sendtoOne(const std::string message) {
  couriers[0].send(message);
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
