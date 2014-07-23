#ifndef MESSAGE_HEADER_HPP
#define MESSAGE_HEADER_HPP

#include <string>
#include <cstdint>

class message_header {
  public:
    static message_header from_string(std::string);
    message_header(
        uint32_t type, uint32_t flags, uint32_t length, uint32_t address);
    const uint32_t type;
    const uint32_t flags;
    const uint32_t length;
    const uint32_t address;
    std::string to_string() const;

    bool operator==(const message_header &other) {
      return type    == other.type &&
             flags   == other.flags &&
             length  == other.length &&
             address == other.address;
    }

    bool operator!=(const message_header &other) { return !(*this == other); }
};

#endif
