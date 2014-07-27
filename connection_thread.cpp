#include "connection_thread.hpp"
#include "socket.hpp"
#include "message.hpp"
#include "invite_request.hpp"
#include "chat_ack.hpp"

using namespace std;

connection_thread::connection_thread(client c) :
  _c(c), _f(message_factory(c.ip_address())) { }

void connection_thread::run() {
  thread t(&connection_thread::process_messages, this);
}

void connection_thread::process_messages() {
  while (true) {
    _c.accept();
    auto s = _c.receive_from_courier();
    auto m = message::from_string(s);
    _c.process_message(m);
  }
}



/* namespace connection_interface { */

/*   void run(client client_ob) { */
/*     std::thread t1(receive_connection, client_ob); */
/*   } */

/*   void receive_connection(client client_ob) { */
/*     message_factory factory = message_factory(myAddr); */
/*     while(1) { */
/*       client_ob.accpet(); */
/*       bool alive = true; */
/*       while(alive) { */
/*         messagestring = client_ob.receiveConnection(); */
/*         message newmessage = message::from_string(messagestring); */
/*         message_header header = newmessage.&header(); */
/*         switch(header -> type) { */
/*           case message_type::LIST_UPDATE: */
/*           case message_type::CHAT_MESSAGE: */
/*             chat_message chat = newmessage.body();//print to the standard output and than send back a ACK message */
/*             std::cout << chat.timestamp() + ":" */
/*           break; */
/*           case message_type::CHAT_ACK:// used to add to the sender to the room member list */
/*             chat_ack body = (chat_ack)newmessage.&body(); */
/*             uint64_t rmid = body.room_id(); */
/*             if (rmid != roomID) { */

/*               break; */
/*             } */
/*             uint32_t ip = header.address; */
/*             std::Pair<std::string,int> sn = peerList.find(ip); */
/*             std::string name = sn.first; */
/*             network::socket move = client_ob.move_to_comm（ip, name); */
/*             sn.second = move; */
/*             alive = false; */
/*             break; */
/*           default: */
/*             cerr << "Invalid Message"; */
/*             break; */
/*         } */
/*       } */

/*     } */
/*   } */

/* } */
