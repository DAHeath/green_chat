#ifndef LIST_UPDATE_HPP
#define LIST_UPDATE_HPP

#include <vector>

#include "message_header.hpp"
#include "message_body.hpp"

class list_update : public message_body {
  public:
    static list_update *from_string(std::string);
    std::string to_string() const;

    list_update(
        uint64_t room_id,
        std::vector<uint32_t> addresses,
        std::vector<std::string> names) :
      _room_id(room_id),
      _addresses(addresses),
      _names(names) { }


    uint64_t room_id() const { return _room_id; }
    std::vector<uint32_t> addresses() const { return _addresses; }
    std::vector<std::string> names() const { return _names; }


    uint32_t length() const;
    uint32_t type() const { return message_type::LIST_UPDATE; }


    bool operator==(const list_update &other) {
      return room_id()   == other.room_id() &&
             addresses() == other.addresses() &&
             names()     == other.names();
    }
    bool operator!=(const list_update &other) { return !(*this==other); }
    bool operator==(const message_body &other) {
      return typeid(*this) == typeid(other) &&
        *this==dynamic_cast<const list_update&>(other);
    }

  private:

    uint64_t _room_id;
    std::vector<uint32_t> _addresses;
    std::vector<std::string> _names;
};

#endif
