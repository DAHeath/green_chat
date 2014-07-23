#ifndef CHAT_ACK_HPP
#define CHAT_ACK_HPP

#include "message_header.hpp"

class chat_ack {
  public:
    static chat_ack from_string(std::string);
    static chat_ack from_data(
        uint32_t addr,
        uint64_t room_id,
        uint32_t timestamp);

    std::string to_string();

    message_header header() const { return _header; }
    uint64_t room_id() const { return _room_id; }
    uint32_t timestamp() const { return _timestamp; }

    bool operator==(const chat_ack &other) {
      return header()    == other.header() &&
             room_id()   == other.room_id() &&
             timestamp() == other.timestamp();
    }
    bool operator!=(const chat_ack &other) { return !(*this==other); }

  private:
    chat_ack(
        message_header header,
        uint64_t room_id,
        uint32_t timestamp) :
      _header(header),
      _room_id(room_id),
      _timestamp(timestamp) { }

    message_header _header;
    uint64_t _room_id;
    uint32_t _timestamp;
};

#endif
