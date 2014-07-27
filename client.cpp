#include "client.hpp"
#include "message_types.hpp"

void client::add_neighbor(
    uint32_t ip_address,
    std::string name,
    unsigned int socket) {
  user u { ip_address, socket, name };

  comm_sockets.push_back(u);
}

void client::remove_neighbor(uint32_t ip_address) {
    unsigned int n;
    for (n = 0; n < comm_sockets.size(); n++) {
      if (comm_sockets[n].has_address(ip_address)) break;
    }
    auto toremove = comm_sockets[n];
    comm_sockets.erase(comm_sockets.begin() + n);
    toremove.close_connection();
}

void client::move_to_comm(uint32_t ip_address, std::string name) {
  network::socket result = couriers[0];
  user u { ip_address, result, name };

  comm_sockets.push_back(u);
  couriers.erase(couriers.begin());
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

void client::make_courier(network::socket newCourier) {
  couriers.push_back(newCourier);
}

void client::accept() {
  auto s = interface.accept();
  couriers.push_back(s);
}
