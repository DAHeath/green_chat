#include "client.hpp"

#include "message_types.hpp"
#include <algorithm>

using namespace std;

void client::process_message(message &m) {
  auto sender_ip = m.header()->address;
  switch (m.header()->type) {
    case message_type::ROOM_QUERY:
      send_room_list(sender_ip);
      break;

    case message_type::INVITE_REQUEST:
      respond_to_invite(m);
      break;

    case message_type::LIST_UPDATE:
      respond_to_update(m);
      break;

    case message_type::CHAT_MESSAGE:
      auto cm = (chat_message*)m.body();
      if (in_room(cm->room_id())) {
        if (!has_roommate(m.header()->address, cm->user_name())) {
          add_roommate(user { m.header()->address, 8000, cm->user_name() });
        }
        cout << cm->user_name() << ": " << cm->message() << "\n";
      }
      break;

  }
}


bool client::has_roommate(uint32_t address, std::string name) {
  for (auto u : roommates) {
    if (address == u.address() && name == u.name()) {
      return true;
    }
  }
  return false;
}

void client::send_room_list(uint32_t address) {
  vector<uint64_t> rooms;
  vector<std::string> room_names;

  if (room_name() != "") {
    rooms.push_back(room_id());
    room_names.push_back(room_name());
  }
  auto room_list = _f.build_room_list(rooms, room_names);
  send_to_courier(address, room_list.to_string());
}

void client::respond_to_invite(message &m) {
  auto ir = (invite_request*)m.body();
  if (ir->id() == room_id()) {
    user u { m.header()->address, courier_at(m.header()->address), ir->user_name() };
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

  auto m = _f.build_add_list_update(room_id(), room_name(), ips, names);
  send_to_courier(u.address(), m.to_string());
}

void client::send_new_user_to_room(user u) {
  vector<uint32_t> ips { u.address() };
  vector<string> names { u.name() };
  auto m = _f.build_add_list_update(room_id(), room_name(), ips, names);
  send(m.to_string());
}

void client::move_user_to_room(user u) {
  add_roommate(u);
  remove_courier(u.address());
}

void client::respond_to_update(message &m) {
  auto lu = (list_update*)m.body();
  if (!in_room()) { set_room(lu->room_id(), lu->room_name()); }
  add_appropriate_users(lu);
}

void client::add_appropriate_users(list_update *lu) {
  if (lu->room_id() == room_id()) {
    for (unsigned int i = 0; i < lu->addresses().size(); i++) {
      if (!has_roommate(lu->addresses()[i], lu->names()[i])) {
        add_roommate(user { lu->addresses()[i], 8000, lu->names()[i] });
      }
    }
  }
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

void client::remove_roommate(uint32_t ip_address) {
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
