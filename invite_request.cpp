#include "invite_request.hpp"

#include "bit_ops.hpp"
#include "message_types.hpp"

using namespace std;

invite_request invite_request::from_string(string s) {
  auto header = message_header::from_string(s.substr(0, 8));
  auto body = s.substr(8, header.length+9);

  auto id = bit::extract64(body);
  auto name = body.substr(8);
  name = name.substr(0, name.size()-1);

  return invite_request { header, id, name };
}

invite_request invite_request::from_data(
    uint32_t addr, uint64_t id, string name) {
  uint32_t length = name.size() + 9;
  message_header header { message_type::INVITE_REQUEST, 0, length, addr };
  return invite_request { header, id, name };
}

string invite_request::to_string() {
  ostringstream ss;
  ss << _header.to_string();
  bit::insert64(ss, _id);
  ss << _name << "\0";
  return ss.str();
}
