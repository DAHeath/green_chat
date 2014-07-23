#ifndef INVITE_REQUEST_HPP
#define INVITE_REQUEST_HPP

#include "message_header.hpp"

class invite_request {
  public:
    static invite_request from_string(std::string);
    static invite_request from_data(
        uint32_t addr, uint64_t id, std::string name);

    invite_request(message_header header, uint64_t id, std::string name) :
      _header(header), _id(id), _name(name) { }

    std::string to_string();

    message_header header() const { return _header; }
    uint64_t id() const { return _id; }
    std::string name() const { return _name; }

    bool operator==(const invite_request &other) {
      return header() == other.header() &&
             id()     == other.id() &&
             name()   == other.name();
    }
    bool operator!=(const invite_request &other) { return !(*this==other); }

  private:
    message_header _header;
    uint64_t _id;
    std::string _name;
};

#endif
