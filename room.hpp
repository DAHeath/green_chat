#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include <vector>
#include <cstdint>

#include "user.hpp"

class room {
  public:
    room(uint64_t id, std::string name) : _id(id), _name(name) { }
    uint64_t id() const { return _id; }
    std::string name() const { return _name; }

    void add_user(user u) : users.push_back(u);
    void broadcast(std::string m) { for (auto u:users) { u.send(m); }}

  private:
    uint64_t _id;
    std::string _name;
    std::vector<user> users;
}

#endif
