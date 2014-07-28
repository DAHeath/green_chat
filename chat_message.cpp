#include "chat_message.hpp"

#include "bit_ops.hpp"
#include "message_types.hpp"

using namespace std;

chat_message *chat_message::from_string(string body) {
  uint64_t room_id = bit::extract64(body);
  body = body.substr(8);
  uint32_t timestamp = bit::extract32(body);
  body = body.substr(4);

  unsigned int divide = body.find('\0') + 1;
  auto user_name = body.substr(0, divide-1);
  body = body.substr(divide);

  return new chat_message { room_id, timestamp, user_name, body };
}

string chat_message::to_string() const {
  ostringstream ss;
  bit::insert64(ss, _room_id);
  bit::insert32(ss, _timestamp);
  ss << _user_name << '\0';
  ss << _message;
  return ss.str();
}
