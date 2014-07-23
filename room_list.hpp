#ifndef ROOM_LIST_HPP
#define ROOM_LIST_HPP

#include <vector>

#include "message_header.hpp"

class room_list {
  public:
    static room_list from_string(std::string);
    static room_list from_data(
        uint32_t addr,
        std::vector<uint64_t> ids,
        std::vector<std::string> names);

    std::string to_string();

    message_header header() const { return _header; }
    std::vector<uint64_t> ids() const { return _ids; }
    std::vector<std::string> names() const { return _names; }

    bool operator==(const room_list &other) {
      return header() == other.header() &&
             ids()    == other.ids() &&
             names()  == other.names();
    }
    bool operator!=(const room_list &other) { return !(*this==other); }

  private:
    room_list(message_header, std::vector<uint64_t>, std::vector<std::string>);

    message_header _header;
    std::vector<uint64_t> _ids;
    std::vector<std::string> _names;
};

#endif
