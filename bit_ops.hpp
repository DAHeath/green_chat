#ifndef BIT_OPS
#define BIT_OPS

#include <sstream>

namespace bit {

  int extract8(std::stringstream& ss) {
    char part;
    ss >> part;
    return part;
  }

  int extract16(std::stringstream& ss) {
    return (extract8(ss) << 8) + extract8(ss);
  }

  int extract32(std::stringstream& ss) {
    return (extract16(ss) << 16) + extract16(ss);
  }

  void insert8(std::ostringstream& ss, int data) {
    char c = data & 0x000000FF;
    ss << c;
  }

  void insert16(std::ostringstream& ss, int data) {
    insert8(ss, data >> 8);
    insert8(ss, data);
  }

  void insert32(std::ostringstream& ss, int data) {
    insert16(ss, data >> 16);
    insert16(ss, data);
  }

};

#endif
