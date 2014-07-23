#include "room_list.hpp"

#include <sstream>

#include "bit_ops.hpp"
#include "message_types.hpp"

using namespace std;

room_list *room_list::from_string(string body) {
  vector<uint64_t> ids;
  vector<string> names;

  unsigned int divide = 0;
  do {
    body = body.substr(divide);
    ids.push_back(bit::extract64(body));
    body = body.substr(8);

    divide = body.find('\0') + 1;
    names.push_back(body.substr(0, divide-1));
  } while (divide < body.size());

  return new room_list { ids, names };
}

string room_list::to_string() const {
  ostringstream ss;
  for (unsigned int i = 0; i < _ids.size(); i++) {
    bit::insert64(ss, _ids[i]);
    ss << _names[i] << '\0';
  }
  return ss.str();
}

uint32_t room_list::length() const {
  uint32_t l = 0;
  for (auto name : _names) { l += 8 + name.size() + 1; }
  return l;
}
