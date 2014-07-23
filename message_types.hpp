#ifndef MESSAGE_TYPES_HPP
#define MESSAGE_TYPES_HPP

enum message_type {
  ROOM_QUERY = 0,
  ROOM_LIST = 1,
  INVITE_REQUEST = 2,
  LIST_UPDATE = 3,
  CHAT_MESSAGE = 4,
  CHAT_ACK = 5,
};

#endif
