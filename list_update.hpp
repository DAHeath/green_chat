#ifndef LIST_UPDATE_HPP
#define LIST_UPDATE_HPP

#include <vector>

#include "message_header.hpp"

class list_update {
  public:
    static list_update from_string(std::string);
    static list_update from_data(
        bool is_add,
        uint32_t addr,
        uint64_t room_id,
        std::vector<uint32_t> addresses,
        std::vector<std::string> names);

    std::string to_string();

    message_header header() const { return _header; }
    uint64_t room_id() const { return _room_id; }
    std::vector<uint32_t> addresses() const { return _addresses; }
    std::vector<std::string> names() const { return _names; }

    bool operator==(const list_update &other) {
      return header()    == other.header() &&
             room_id()   == other.room_id() &&
             addresses() == other.addresses() &&
             names()     == other.names();
    }
    bool operator!=(const list_update &other) { return !(*this==other); }

  private:
    list_update(
        message_header header,
        uint64_t room_id,
        std::vector<uint32_t> addresses,
        std::vector<std::string> names) :
      _header(header),
      _room_id(room_id),
      _addresses(addresses),
      _names(names) { }

    message_header _header;
    uint64_t _room_id;
    std::vector<uint32_t> _addresses;
    std::vector<std::string> _names;
};

#endif
