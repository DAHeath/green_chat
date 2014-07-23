#ifndef MESSAGE_BODY_HPP
#define MESSAGE_BODY_HPP

#include <string>
#include <typeinfo>
#include <cstdint>

#include "message_types.hpp"

class message_body {
  public:
    virtual ~message_body() { }
    virtual std::string to_string() const = 0;
    virtual bool operator==(const message_body &other)=0;
    bool operator!=(const message_body &other) {
      return !(*this==other);
    }

    virtual uint32_t length() const = 0;
    virtual uint32_t type() const = 0;
};

#endif
