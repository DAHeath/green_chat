#include "room_list.hpp"

#include <sstream>

#include "bit_ops.hpp"
#include "message_types.hpp"

using namespace std;

room_list room_list::from_string(string s) {
  auto header = message_header::from_string(s.substr(0, 8));
  auto body = s.substr(8, header.length+9);

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

  return room_list { header, ids, names };
}

room_list room_list::from_data(
    uint32_t address,
    vector<uint64_t> ids,
    vector<string> names) {

  uint32_t length = 0;
  for (auto n : names) { length += n.size() + 9; } // 8 for id and 1 for '\n'
  message_header header { message_type::ROOM_LIST, 0, length, address };
  return room_list { header, ids, names };
}


room_list::room_list(message_header h, vector<uint64_t> i, vector<string> n) :
  _header(h), _ids(i), _names(n) { }

string room_list::to_string() {
  ostringstream ss;
  ss << _header.to_string();
  for (unsigned int i = 0; i < _ids.size(); i++) {
    bit::insert64(ss, _ids[i]);
    ss << _names[i] << '\0';
  }
  return ss.str();
}
