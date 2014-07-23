#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include "message_header.hpp"
#include "message_body.hpp"

#include <iostream>

class message {
  public:
    static message from_string(std::string);
    static message from_body(uint32_t addr, uint8_t flags, message_body *body);

    message(message_header *header, message_body *body) :
      _header(header), _body(body) { }

    ~message() {
      delete _header;
      delete _body;
    }

    std::string to_string() const {
      return _header->to_string() + _body->to_string();
    }

    message_header &header() const { return *_header; }
    message_body &body() const { return *_body; }

    bool operator==(const message &other) {
      return body() == other.body() && header() == other.header();
    }
    bool operator!=(const message &other) { return !(*this==other); }

  private:
    message_header *_header;
    message_body *_body;
};

#endif
