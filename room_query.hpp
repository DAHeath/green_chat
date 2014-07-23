#ifndef ROOM_QUERY_HPP
#define ROOM_QUERY_HPP

#include "message_body.hpp"

#include <iostream>

class room_query : public message_body {
  public:
    std::string to_string() const { return ""; }
    bool operator==(const message_body &other) {
      return typeid(*this) == typeid(other);
    }
    uint32_t length() const { return 0; }
    uint32_t type() const { return message_type::ROOM_QUERY; }
};

#endif
