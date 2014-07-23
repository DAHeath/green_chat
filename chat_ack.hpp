#ifndef CHAT_ACK_HPP
#define CHAT_ACK_HPP

#include "message_header.hpp"

class chat_ack {
  public:
    static chat_ack from_string(std::string);
    static chat_ack from_data(uint32_t t, uint64_t id);
    
    chat_ack(uint32_t t, uint64_t id) : 
      _t(t), _id(id) { }
      
    std::string to_string();
    
    message_header header() const { return _header; }
    uint64_t id() const { return _id; }
    uint32_t t() const { return _t; }
    
    bool operator==(const chat_ack &other) {
      return header() == other.header() &&
             id()     == other.id() &&
             t()   == other.t();
    }
    bool operator!=(const chat_ack &other) { return !(*this==other); }
    
    private:
      message_header _header;
      uint64_t _id;
      uint32_t _t;
};

#endif