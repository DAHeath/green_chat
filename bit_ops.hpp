#ifndef BIT_OPS
#define BIT_OPS

#include <sstream>

namespace bit {

  uint32_t extract8(std::stringstream& ss);
  uint32_t extract16(std::stringstream& ss);
  uint32_t extract32(std::stringstream& ss);
  uint64_t extract64(std::stringstream& ss);

  uint32_t extract32(std::string& s);
  uint64_t extract64(std::string& s);

  void insert8(std::ostringstream& ss, uint32_t data);
  void insert16(std::ostringstream& ss, uint32_t data);
  void insert32(std::ostringstream& ss, uint32_t data);
  void insert64(std::ostringstream& ss, uint64_t data);

};

#endif
