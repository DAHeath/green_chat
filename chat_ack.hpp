#ifndef CHAT_ACK_HPP
#define CHAT_ACK_HPP

#include "message_header.hpp"
#include "message_body.hpp"

class chat_ack : public message_body {
  public:
    static chat_ack *from_string(std::string);

    chat_ack( uint64_t room_id, uint32_t timestamp) :
      _room_id(room_id), _timestamp(timestamp) { }


    std::string to_string() const;

    uint64_t room_id() const { return _room_id; }
    uint32_t timestamp() const { return _timestamp; }

    uint32_t length() const { return 12; }
    uint32_t type() const { return message_type::CHAT_ACK; }

    bool operator==(const chat_ack &other) {
      return room_id()   == other.room_id() &&
             timestamp() == other.timestamp();
    }
    bool operator!=(const chat_ack &other) { return !(*this==other); }

    bool operator==(const message_body &other) {
      return typeid(*this) == typeid(other) &&
        *this==dynamic_cast<const chat_ack&>(other);
    }

  private:
    uint64_t _room_id;
    uint32_t _timestamp;
};

#endif
