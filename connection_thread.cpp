#include "connection_thread.hpp"
#include "socket.hpp"


namespace connection_interface {

  void run(client client_ob) {
    std::thread t1(receive_connection, client_ob);
  }

  void receive_connection(client client_ob) {
    while(1) {
      client_ob.accpet();
      message newmessage = message::from_string(messagestring);
      message_header header = newmessage.header();
      switch(header -> type) {
        case message_type::ROOM_QUERY:// send back a list of room members

          break;
        case message_type::INVITE_REQUEST: // send everyone else in the room a "add" update list, and the new one a complete list of members

          break;
        /**
        case message_type::LIST_UPDATE:
          updatelist(header -> flags, (list_update) newmessage.body(), client_ob);
          break;
        case message_type::CHAT_MESSAGE:
          chat_message chat = newmessage.body();//print to the standard output and than send back a ACK message
          std::cout << chat.timestamp() + ":"
          break;
        */
        case message_type::CHAT_ACK:// used to add to the sender to the room member list

          break;
        default:
          cerr << "Invalid Message";
          break;
        }
    }
  }

}
