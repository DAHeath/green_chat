#include "client.hpp"

#include "message_types.hpp"
#include <algorithm>

using namespace std;

void client::process_message(message m) {
  auto sender_ip = m.header().address;
  switch (m.header().type) {
    case message_type::ROOM_QUERY:
      send_room_list(sender_ip);
      break;

    case message_type::INVITE_REQUEST:
      respond_to_invite(m);
      break;

    case message_type::LIST_UPDATE:
      auto lu = (list_update&)m.body();
      if (lu.room_id() == room_id()) {
        for (unsigned int i = 0; i < lu.addresses().size(); i++) {
        }
      }
    break;
  }
}

void client::send_room_list(uint32_t address) {
  vector<uint64_t> rooms;
  vector<std::string> roomNames;

  if (room_name() != "") {
    rooms.push_back(room_id());
    roomNames.push_back(room_name());
  }
  auto room_list = _f.build_room_list(rooms, roomNames);
  send_to_courier(address, room_list.to_string());
}

void client::respond_to_invite(message &m) {
  auto ir = (invite_request&)m.body();
  if (ir.id() == room_id()) {
    user u { m.header().address, courier_at(m.header().address), ir.user_name() };

    send_names_list_to_new_user(u);
    send_new_user_to_room(u);
    move_user_to_room(u);

  }
}

void client::send_names_list_to_new_user(user u) {
  vector<uint32_t> ips;
  vector<string> names;

  for (auto r : roommates) {
    ips.push_back(r.address());
    names.push_back(r.name());
  }

  ips.push_back(ip_address());
  names.push_back(name());

  auto m = _f.build_add_list_update(room_id(), ips, names);
  send_to_courier(u.address(), m.to_string());
}

void client::send_new_user_to_room(user u) {
  vector<uint32_t> ips { u.address() };
  vector<string> names { u.name() };
  auto m = _f.build_add_list_update(room_id(), ips, names);
  send(m.to_string());
}

void client::move_user_to_room(user u) {
  add_neighbor(u);
  remove_courier(u.address());
}

class no_such_courier{ };
network::socket client::courier_at(uint32_t address) {
  for (auto s : couriers) { 
    if (s.address() == address) return s; 
  }
  throw no_such_courier();
}

void client::remove_courier(uint32_t address) {
  auto s = courier_at(address);
  couriers.erase(
      remove(couriers.begin(), couriers.end(), s), couriers.end());
}

void client::send_to_courier(uint32_t address, string message) {
  courier_at(address).send(message);
}

void client::remove_neighbor(uint32_t ip_address) {
    unsigned int n;
    for (n = 0; n < roommates.size(); n++) {
      if (roommates[n].has_address(ip_address)) break;
    }
    auto toremove = roommates[n];
    roommates.erase(roommates.begin() + n);
    toremove.close_connection();
}

void client::send(std::string message) {
  for (auto s : roommates) { s.send(message); }
}


std::string client::receive() {
  std::string message = "";
  for (auto s : roommates) {
    message = s.receive(1024);
    if (message != "") return message;
  }
  return message;
}

std::string client::receive_from_courier() {
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
