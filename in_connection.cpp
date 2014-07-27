#include "in_connection.cpp"
#include "message.hpp"
#include "room_list.hpp"
#include "chat_message.hpp"
#include "message_factory.hpp"
#include "time.h"


extern uint32_t myAddr;
extern std::Map<uint32_t,std::Pair<std::string,int>> peerList;// wait, why is it a int for socket?
extern uint64_t roomID;

namespace inmessage {

  void run(client client_ob) {
    std::thread t1(receive_messages, client_ob);
  }

  void receive_messages(client client_ob) {
    message_factory factory = message_factory(myAddr);
    while (1){
      std::string messagestring = client_ob.receive();
      message newmessage = message::from_string(messagestring);
      message_header header = newmessage.&header();
      switch(header -> type) {
        /**
        case message_type::ROOM_QUERY:

          return message(header, new room_query());
          break;
        case message_type::ROOM_LIST:

          return message(header, room_list::from_string(body_text));
          break;
        case message_type::INVITE_REQUEST:

          return message(header, invite_request::from_string(body_text));
          break;
        */
        case message_type::LIST_UPDATE:
          updatelist(header -> flags, (list_update) newmessage.&body(), client_ob);
          break;
        case message_type::CHAT_MESSAGE:
          chat_message chat = (chat_message)newmessage.&body();//print to the standard output and than send back a ACK message
          uint64_t indenti = chat.room_id();
          if (indenti != roomID) { break;}
          uint32_t ip = header.address;
          std::Pair<std::string,int> sn = peerList.find(ip);
          if (sn == null) { break;}
          std::cout << chat.timestamp() + " " + sn.first +  " : " + chat.message();//add timestampstring
          /**
          time_t timer;
          time(&timer);
          tm* tmtime = localime(&time);
          timer = mktime(tmtime);*/
          message ack = factory.build_chat_ack(roomID, static_cast<uint32_t>(time(NULL)));//tmestamps!
          sn.second.send(ack.to_string());
          break;
        case message_type::CHAT_ACK:
          break;
        default:
          break;
      }

    }
  }

  void updatelist(uint32_t flag, list_update body, client client_ob) {
    std::vector<uint32_t> addresses = body.addresses();
    std::vector<std::string> names = body.names();
    uint32_t length = body.length();
    for (int n = 0; n < length; n++) {
      if (flag) {
        client_ob.delete_neighbor(addresses[n]);// this may have to be modified, according to the way client track member list
        /**
        std::Pair<std::string,int> sn = peerList.find(addresses[n]);
        if (sn == null) { continue;}
        network::socket tomove = sn.second
        tomove.close();*/
        peerList.erase(address[n]);
      } else {
        network::socket toadd = client_ob.add_neighbor(addresses[n], 8000);
        peerList.insert(addresses[n], std::pair<std::string,int>(names[n], toadd));
      }
    }
  }

}