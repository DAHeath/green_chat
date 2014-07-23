#include "message.hpp"

#include "message_types.hpp"
#include "room_query.hpp"
#include "room_list.hpp"
#include "invite_request.hpp"
#include "list_update.hpp"
#include "chat_message.hpp"
#include "chat_ack.hpp"

using namespace std;

class invalid_message_type { };

message message::from_string(string s) {
  auto header = message_header::from_string(s.substr(0, 8));

  auto body_text = s.substr(8, header->length+9);

  switch (header->type) {
    case message_type::ROOM_QUERY:
      return message(header, new room_query()); 
    case message_type::ROOM_LIST:
      return message(header, room_list::from_string(body_text));
    case message_type::INVITE_REQUEST:
      return message(header, invite_request::from_string(body_text));
    case message_type::LIST_UPDATE:
      return message(header, list_update::from_string(body_text));
    case message_type::CHAT_MESSAGE:
      return message(header, chat_message::from_string(body_text));
    case message_type::CHAT_ACK:
      return message(header, chat_ack::from_string(body_text));
    default:
      throw invalid_message_type();
  }
}
