#ifndef ROOM_LIST_HPP
#define ROOM_LIST_HPP

#include <string>
#include <vector>
#include <cstdint>

#include "message_header.hpp"

class room_list {
  public:
    static room_list from_string(std::string);
    room_list(message_header, std::vector<uint64_t>, std::vector<std::string>);

    std::string to_string();

    const std::vector<uint64_t> ids;
    const std::vector<std::string> names;
    const message_header header;
  private:
};

#endif
