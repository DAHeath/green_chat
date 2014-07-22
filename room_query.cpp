#include "room_query.hpp"

#include "message_types.hpp"

using namespace std;

room_query room_query::from_string(string s) {
  auto header = message_header::from_string(s);
  return room_query(header);
}

room_query room_query::from_address(uint32_t addr) {
  message_header header { message_type::ROOM_QUERY, 0, 0, addr };
  return room_query(header);
}

string room_query::to_string() {
  return _header.to_string();
}
