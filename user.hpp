#ifndef USER_HPP
#define USER_HPP

#include <string>
#include <cstdint>

#include "socket.hpp"

class user {
  public:
    user(uint32_t address, uint32_t def_port, std::string name) :
      _address(address),
      _name(name),
      s(network::socket::connected(address, def_port)) { }

    user(uint32_t address, network::socket _s, std::string name) :
      _address(address),
      _name(name),
      s(_s) { }


    uint32_t address() const { return _address; }
    std::string name() const { return _name; }

    void send(std::string message) { s.send(message); }
    std::string receive(unsigned int size) { return s.receive(size); }

    bool has_address(uint32_t address) { return _address == address; }

    void close_connection() { s.close(); }

  private:
    uint32_t _address;
    std::string _name;
    network::socket s;
};

#endif
