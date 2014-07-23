#include "list_update.hpp"

#include <sstream>

#include "bit_ops.hpp"
#include "message_types.hpp"

using namespace std;

list_update list_update::from_string(string s) {
  auto header = message_header::from_string(s.substr(0, 8));
  auto body = s.substr(8, header.length+9);

  uint64_t room_id = bit::extract64(body);
  body = body.substr(8);

  vector<uint32_t> addresses;
  vector<string> names;
  unsigned int divide = 0;
  do {
    body = body.substr(divide);
    addresses.push_back(bit::extract32(body));
    body = body.substr(4);

    divide = body.find('\0') + 1;
    names.push_back(body.substr(0, divide-1));
  } while (divide < body.size());

  return list_update { header, room_id, addresses, names };
}

list_update list_update::from_data(
        bool is_add,
        uint32_t addr,
        uint64_t room_id,
        std::vector<uint32_t> addresses,
        std::vector<std::string> names) {

  uint32_t length = 8; // 8 for room id
  for (auto n : names) { length += n.size() + 5; } // 4 for address, 1 for '\0'

  uint32_t flags = 0;
  if (!is_add) { flags = 1; }

  message_header header { message_type::LIST_UPDATE, flags, length, addr };
  return list_update { header, room_id, addresses, names };
}

string list_update::to_string() {
  ostringstream ss;
  ss << _header.to_string();
  bit::insert64(ss, _room_id);
  for (unsigned int i = 0; i < _names.size(); i++) {
    bit::insert32(ss, _addresses[i]);
    ss << _names[i] << '\0';
  }
  return ss.str();
}
