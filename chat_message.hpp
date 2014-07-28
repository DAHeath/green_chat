#ifndef CHAT_MESSAGE_HPP
#define CHAT_MESSAGE_HPP

#include "message_body.hpp"

class chat_message : public message_body {
  public:
    static chat_message *from_string(std::string);

    chat_message(
        uint64_t room_id,
        uint32_t timestamp,
        std::string user_name,
        std::string message) :
      _room_id(room_id),
      _timestamp(timestamp),
      _user_name(user_name),
      _message(message) { }

    std::string to_string() const;

    uint64_t room_id() const { return _room_id; }
    uint32_t timestamp() const { return _timestamp; }
    std::string user_name() const { return _user_name; }
    std::string message() const { return _message; }

    uint32_t length() const { return 8 + 4 + _message.size(); }
    uint32_t type() const { return message_type::CHAT_MESSAGE; }

    bool operator==(const chat_message &other) {
      return room_id()   == other.room_id() &&
             timestamp() == other.timestamp() &&
             user_name() == other.user_name() &&
             message()   == other.message();
    }
    bool operator!=(const chat_message &other) { return !(*this==other); }

    bool operator==(const message_body &other) {
      return typeid(*this) == typeid(other) &&
        *this==dynamic_cast<const chat_message&>(other);
    }

  private:
    uint64_t _room_id;
    uint32_t _timestamp;
    std::string _user_name;
    std::string _message;

};

#endif
