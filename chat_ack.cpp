#include "chat_ack.hpp"

#include "bit_ops.hpp"
#include "message_types.hpp"

using namespace std;

chat_ack chat_ack::from_string(string s) {
  auto header = message_header::from_string(s.substr(0, 8));
  auto body = s.substr(8, header.length+9);

  auto id = bit::extract64(body);
  auto name = body.substr(8);
  name = name.substr(0, name.size());

  return chat_ack { header, id, name };
}

chat_ack chat_ack::from_data(
    uint32_t addr, uint64_t id, string name) {
  uint32_t length = name.size() + 9;
  message_header header { message_type::CHAT_ACK, 0, length, addr };
  return chat_ack { header, id, name };
}

string chat_ack::to_string() {
  ostringstream ss;
  ss << _header.to_string();
  bit::inster32(ss, _t);
  bit::insert64(ss, _id);
  return ss.str();
}
