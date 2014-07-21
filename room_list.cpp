#include "room_list.hpp"

#include <sstream>
#include <iostream>

#include "bit_ops.hpp"

using namespace std;

room_list room_list::from_string(std::string s) {
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

  return room_list(header, ids, names);
}

room_list::room_list(message_header h, vector<uint64_t> i, vector<string> n) :
  header(h), ids(i), names(n) { }

string room_list::to_string() {
  ostringstream ss;
  ss << header.to_string();
  for (unsigned int i = 0; i < ids.size(); i++) {
    bit::insert64(ss, ids[i]);
    ss << names[i] << '\0';
  }
  return ss.str();
}
