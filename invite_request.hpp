#ifndef INVITE_REQUEST_HPP
#define INVITE_REQUEST_HPP

#include "message_body.hpp"

class invite_request : public message_body {
  public:
    static invite_request *from_string(std::string);

    invite_request(uint64_t id, std::string name) :
      _id(id), _name(name) { }

    std::string to_string() const;

    uint64_t id() const { return _id; }
    std::string name() const { return _name; }

    uint32_t length() const { return _name.size() + 0; }
    uint32_t type() const { return message_type::INVITE_REQUEST; }

    bool operator==(const invite_request &other) {
      return id()     == other.id() &&
             name()   == other.name();
    }
    bool operator!=(const invite_request &other) { return !(*this==other); }

    bool operator==(const message_body &other) {
      return typeid(*this) == typeid(other) &&
        *this==dynamic_cast<const invite_request&>(other);
    }
  private:
    uint64_t _id;
    std::string _name;
};

#endif
