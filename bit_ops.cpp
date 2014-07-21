#include "bit_ops.hpp"

#include <cstdint>

namespace bit {

  uint32_t extract8(std::stringstream& ss) {
    char part;
    ss >> part;
    return part;
  }

  uint32_t extract16(std::stringstream& ss) {
    return (extract8(ss) << 8) + extract8(ss);
  }

  uint32_t extract32(std::stringstream& ss) {
    return (extract16(ss) << 16) + extract16(ss);
  }

  uint64_t extract64(std::stringstream& ss) {
    uint64_t first = extract32(ss);
    return (first << 32) + extract32(ss);
  }

  uint64_t extract64(std::string& s) {
    std::stringstream ss(s);
    return extract64(ss);
  }

  void insert8(std::ostringstream& ss, uint32_t data) {
    char c = data & 0x000000FF;
    ss << c;
  }

  void insert16(std::ostringstream& ss, uint32_t data) {
    insert8(ss, data >> 8);
    insert8(ss, data);
  }

  void insert32(std::ostringstream& ss, uint32_t data) {
    insert16(ss, data >> 16);
    insert16(ss, data);
  }

  void insert64(std::ostringstream& ss, uint64_t data) {
    insert32(ss, data >> 32);
    insert32(ss, data);
  }

};
