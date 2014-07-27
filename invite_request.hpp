#ifndef INVITE_REQUEST_HPP
#define INVITE_REQUEST_HPP

#include "message_body.hpp"

class invite_request : public message_body {
  public:
    static invite_request *from_string(std::string);

    invite_request(uint64_t id, std::string room_name, std::string user_name) :
      _id(id), _room_name(room_name), _user_name(user_name) { }

    std::string to_string() const;

    uint64_t id() const { return _id; }
    std::string room_name() const { return _room_name; }
    std::string user_name() const { return _user_name; }

    uint32_t length() const { return _room_name.size() + _user_name.size() + 8; }
    uint32_t type() const { return message_type::INVITE_REQUEST; }

    bool operator==(const invite_request &other) {
      return id()        == other.id() &&
             room_name() == other.room_name();
             user_name() == other.user_name();
    }
    bool operator!=(const invite_request &other) { return !(*this==other); }

    bool operator==(const message_body &other) {
      return typeid(*this) == typeid(other) &&
        *this==dynamic_cast<const invite_request&>(other);
    }
  private:
    uint64_t _id;
    std::string _room_name;
    std::string _user_name;
};

#endif
