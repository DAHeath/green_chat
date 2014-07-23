#ifndef ROOM_QUERY_HPP
#define ROOM_QUERY_HPP

#include "message_header.hpp"

class room_query {
  public:
    static room_query from_string(std::string);
    static room_query from_address(uint32_t addr);

    std::string to_string();

    message_header header() const { return _header; }

    bool operator==(const room_query &other) {
      return header() == other.header();
    }
    bool operator!=(const room_query &other) { return !(*this==other); }

  private:
    room_query(message_header header) : _header(header) { }

    message_header _header;
};

#endif
