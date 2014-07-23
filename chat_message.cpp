#include "chat_message.hpp"

#include "bit_ops.hpp"
#include "message_types.hpp"

using namespace std;

chat_message chat_message::from_string(string s) {
  auto header = message_header::from_string(s.substr(0, 8));
  auto body = s.substr(8, header.length+9);

  uint64_t room_id = bit::extract64(body);
  body = body.substr(8);
  uint32_t timestamp = bit::extract32(body);
  body = body.substr(4);

  return chat_message { header, room_id, timestamp, body };
}

chat_message chat_message::from_data(
    uint32_t addr,
    uint64_t room_id,
    uint32_t timestamp,
    std::string message) {

  uint32_t length = 8 + 4 + message.size();

  message_header header { message_type::CHAT_MESSAGE, 0, length, addr };
  return chat_message { header, room_id, timestamp, message };
}

string chat_message::to_string() {
  ostringstream ss;
  ss << _header.to_string();
  bit::insert64(ss, _room_id);
  bit::insert32(ss, _timestamp);
  ss << _message;
  return ss.str();
}
