#ifndef MESSAGE_FACTORY_HPP
#define MESSAGE_FACTORY_HPP

#include "message.hpp"

#include "room_list.hpp"
#include "room_query.hpp"
#include "invite_request.hpp"
#include "list_update.hpp"
#include "chat_message.hpp"
#include "chat_ack.hpp"

class message_factory {
  public:

    message_factory(uint32_t address) : addr(address) { }

    message build_room_query() {
      return message::from_body(addr, 0, new room_query);
    }
    message build_room_list(
        std::vector<uint64_t> ids,
        std::vector<std::string> names) {
      return message::from_body(addr, 0, new room_list(ids, names));
    }
    message build_invite_request(
        uint64_t id,
        std::string room_name,
        std::string user_name) {
      return message::from_body(addr, 0, new invite_request(
            id, room_name, user_name));
    }
    message build_add_list_update(
        uint64_t room_id,
        std::string room_name,
        std::vector<uint32_t> addresses,
        std::vector<std::string> names) {
      return message::from_body(
          addr, 1, new list_update(room_id, room_name, addresses, names));
    }
    message build_remove_list_update(
        uint64_t room_id,
        std::string room_name,
        std::vector<uint32_t> addresses,
        std::vector<std::string> names) {
      return message::from_body(
          addr, 0, new list_update(room_id, room_name, addresses, names));
    }
    message build_chat_message(
        uint64_t room_id,
        uint32_t timestamp,
        std::string name,
        std::string text) {
      return message::from_body(
          addr, 0, new chat_message(room_id, timestamp, name, text));
    }
    message build_chat_ack(uint64_t room_id, uint32_t timestamp) {
      return message::from_body(addr, 0, new chat_ack(room_id, timestamp));
    }

  private:
    uint32_t addr;
};

#endif
