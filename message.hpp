#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <string>

class message {
  public:
    static message from_string(std::string);
    message(int type, int flags, int length, int address, std::string data);
    const int type;
    const int flags;
    const int length;
    const int address;
    const std::string data;
    std::string to_string();
};

#endif
