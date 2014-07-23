#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include "message_header.hpp"

class chat_message {
  public:
    static chat_message from_string(std::string);
    static chat_message from_data(
        uint32_t addr,
        uint64_t room_id,
        uint32_t timestamp,
        std::string message);

    std::string to_string();

    message_header header() const { return _header; }
    uint64_t room_id() const { return _room_id; }
    uint32_t timestamp() const { return _timestamp; }
    std::string message() const { return _message; }

    bool operator==(const chat_message &other) {
      return header()    == other.header() &&
             room_id()   == other.room_id() &&
             timestamp() == other.timestamp() &&
             message()   == other.message();
    }
    bool operator!=(const chat_message &other) { return !(*this==other); }

  private:
    chat_message(
        message_header header,
        uint64_t room_id,
        uint32_t timestamp,
        std::string message) :
      _header(header),
      _room_id(room_id),
      _timestamp(timestamp),
      _message(message) { }

    message_header _header;
    uint64_t _room_id;
    uint32_t _timestamp;
    std::string _message;

};

#endif
