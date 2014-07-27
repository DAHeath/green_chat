#include "connection_thread.hpp"
#include "socket.hpp"
#include "message.hpp"
#include "invite_request.hpp"
#include "chat_ack.hpp"

extern uint32_t myAddr;
extern std::string username;
extern std::Map<uint32_t,std::Pair<std::string,int>> peerList;
extern uint64_t roomID;
extern std::string roomName;

namespace connection_interface {

  void run(client client_ob) {
    std::thread t1(receive_connection, client_ob);
  }

  void receive_connection(client client_ob) {
    message_factory factory = message_factory(myAddr);
    while(1) {
      client_ob.accpet();
      bool alive = true;
      while(alive) {
        messagestring = client_ob.receiveConnection();
        message newmessage = message::from_string(messagestring);
        message_header header = newmessage.&header();
        switch(header -> type) {
          case message_type::ROOM_QUERY:// send back a list of room members
            std::vector<uint64_t> rooms;
            rooms.push_back(roomID);
            std::vector<std::string> roomNames;
            roomNames.push_back(roomName);
            message roomquery = factory.build_room_list(rooms, roomNames);
            client_ob.sendtoOne(message.to_string());
            break;
          case message_type::INVITE_REQUEST: // send everyone else in the room a "add" update list, and the new one a complete list of members
            invite_request body = (invite_request)newmessage.&body();
            uint64_t roomid = body.id();
            //if (roomid != roomID) { break;}// QUESTION: if the room id in the message not right, should I close the socket?
            std::string name = body.user_name();//get the name TODO: add the function in invite_request class
            uint32_t ip = header.address;//get the ip
            std::vector<uint32_t> ids;
            ids.push_back(ip);
            std::vector<std::string> names;
            names.push_back(name);
            message listupdate = factory.build_add_list_update(roomID, ids, names);
            client_ob.send(listupdate.to_string());
            ids = client_ob.getaddresses();
            names = client_ob.getnames();
            ids.push_back(myAddr);// the connector's address and name is appended last, so the connection currently established can be handled
            names.push_back(username);
            listupdate = factory.build_add_list_update(roomID, ids, names);
            client_ob.sendtoOne(listupdate.to_string());
            alive = false;
            network::socket s = client_ob.move_to_comm(name, ip);
            // TODO: should also modify the MAP peerlist! DONE
            peerList.insert(ip, std::pair<std::string,int>(name, s));
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
            chat_ack body = (chat_ack)newmessage.&body();
            uint64_t rmid = body.room_id();
            /**if (rmid != roomID) {

              break;
            }*/
            uint32_t ip = header.address;
            std::Pair<std::string,int> sn = peerList.find(ip);
            std::string name = sn.first;
            network::socket move = client_ob.move_to_comm（ip, name);
            sn.second = move;
            alive = false;
            break;
          default:
            cerr << "Invalid Message";
            break;
        }
      }

    }
  }

}
