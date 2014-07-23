#include "chat_ack.hpp"

#include "bit_ops.hpp"
#include "message_types.hpp"

using namespace std;

chat_ack chat_ack::from_string(string s) {
  auto header = message_header::from_string(s.substr(0, 8));
  auto body = s.substr(8, header.length+9);

  uint64_t room_id = bit::extract64(body);
  body = body.substr(8);
  uint32_t timestamp = bit::extract32(body);

  return chat_ack { header, room_id, timestamp };
}

chat_ack chat_ack::from_data(
    uint32_t addr,
    uint64_t room_id,
    uint32_t timestamp) {

  uint32_t length = 8 + 4;

  message_header header { message_type::CHAT_ACK, 0, length, addr };
  return chat_ack { header, room_id, timestamp };
}

string chat_ack::to_string() {
  ostringstream ss;
  ss << _header.to_string();
  bit::insert64(ss, _room_id);
  bit::insert32(ss, _timestamp);
  return ss.str();
}
