#include "list_update.hpp"

#include <sstream>

#include "bit_ops.hpp"
#include "message_types.hpp"

using namespace std;

list_update *list_update::from_string(string body) {
  uint64_t room_id = bit::extract64(body);
  body = body.substr(8);

  unsigned int divide = body.find('\0') + 1;
  auto room_name = body.substr(0, divide-1);

  body = body.substr(divide);

  vector<uint32_t> addresses;
  vector<string> names;
  divide = 0;
  do {
    body = body.substr(divide);
    addresses.push_back(bit::extract32(body));
    body = body.substr(4);

    divide = body.find('\0') + 1;
    names.push_back(body.substr(0, divide-1));
  } while (divide < body.size());

  return new list_update { room_id, room_name, addresses, names };
}

uint32_t list_update::length() const {
  uint32_t length = 8; // 8 for room id
  for (auto n : _names) { length += n.size() + 5; } // 4 for address, 1 for '\0'
  return length;
}

string list_update::to_string() const {
  ostringstream ss;
  bit::insert64(ss, _room_id);
  ss << _room_name << '\0';
  for (unsigned int i = 0; i < _names.size(); i++) {
    bit::insert32(ss, _addresses[i]);
    ss << _names[i] << '\0';
  }
  return ss.str();
}
