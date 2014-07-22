#ifndef INVITE_REQUEST_HPP
#define INVITE_REQUEST_HPP

#include "message_header.hpp"

class invite_request {
  public:
    static invite_request from_string(std::string);
    static invite_request from_data(uint32_t addr, uint64_t id, std::string name);
    invite_request(message_header header, uint64_t id, std::string name) :
      _header(header), _id(id), _name(name) { }

    std::string to_string();

  private:
    message_header _header;
    uint64_t _id;
    std::string _name;
};

#endif
