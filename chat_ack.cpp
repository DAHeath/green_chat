#include "chat_ack.hpp"

#include "bit_ops.hpp"
#include "message_types.hpp"

using namespace std;

chat_ack *chat_ack::from_string(string body) {
  uint64_t room_id = bit::extract64(body);
  body = body.substr(8);
  uint32_t timestamp = bit::extract32(body);

  return new chat_ack { room_id, timestamp };
}

string chat_ack::to_string() const {
  ostringstream ss;
  bit::insert64(ss, _room_id);
  bit::insert32(ss, _timestamp);
  return ss.str();
}
