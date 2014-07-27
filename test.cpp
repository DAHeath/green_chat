#include "socket.hpp"
#include "client.hpp"

#include "user.hpp"

#include "message.hpp"
#include "message_header.hpp"
#include "message_body.hpp"
#include "message_types.hpp"
#include "message_factory.hpp"
#include "bit_ops.hpp" 
#include <iostream>
#include <cstdint>
#include <assert.h>
#include <sstream>

using namespace std;

void test(client c1, client c2, message m) {
  auto s1 = m.to_string();
  assert(m == message::from_string(s1));
  c1.send(m.to_string());
  auto s = c2.receive_from_courier();
  assert(m == message::from_string(s));
}

void make_and_test(client c1, client c2, message_body *body, uint32_t addr) {
  auto m = message::from_body(addr, 0, body);
  c1.send(m.to_string());
  auto s = c2.receive();
  assert(m == message::from_string(s));
}

void test_room_query(client c1, client c2, message_factory f) {
  test(c1, c2, f.build_room_query());
}

void test_room_list(client c1, client c2, message_factory f) {
  vector<uint64_t> ids { 0x1050, 0x1050105010501050 };
  vector<string> names { "ROOM1", "ROOM2" };

  test(c1, c2, f.build_room_list(ids, names));
}


void test_invite_request(client c1, client c2, message_factory f) {
  test(c1, c2, f.build_invite_request(0x1050, "ROOM1", "USER1"));
}


void test_list_update(client c1, client c2, message_factory f) {
  uint64_t room_id { 0x1050 };
  vector<uint32_t> addresses { 0x3333, 0x33333333 };
  vector<string> names { "User1", "Superdupername!" };

  test(c1, c2, f.build_add_list_update(room_id, addresses, names));
}

void test_chat_message(client c1, client c2, message_factory f) {
  uint64_t room_id { 0x1050 };
  uint32_t timestamp { 0x13231323 };
  string mes { "This is just a test message." };

  test(c1, c2, f.build_chat_message(room_id, timestamp, mes));
}

void test_chat_ack(client c1, client c2, message_factory f) {
  uint64_t room_id { 0x1050 };
  uint32_t timestamp { 0x13231323 };

  test(c1, c2, f.build_chat_ack(room_id, timestamp));
}

void run(string address) {
  uint32_t addr = network::interpret_address(address);

  message_factory f { addr };

  auto c1 = client("David", addr, 3456);
  auto c2 = client("Other", addr, 4567);
  auto c3 = client("Dude", addr, 6789);

  c1.add_courier(network::socket::connected(addr, 4567));
  c2.accept();

  c2.set_room(45678, "ROOM!");
  c1.send_to_courier(addr, f.build_room_query().to_string());

  auto s = c2.receive_from_courier();
  auto m = message::from_string(s);

  c2.process_message(m);

  auto s2 = c1.receive_from_courier();

  auto m2 = message::from_string(s2);
  std::cerr << m2.header().type << "\n";
  auto &rl = (room_list&)m2.body();
  std::cerr << rl.names()[0] << "\n";



  /* user u { addr, 4567, "NEIGHBOR" }; */
  /* c1.add_neighbor(u); */
  /* c2.accept(); */

  /* test_room_query(c1, c2, f); */
  /* test_room_list(c1, c2, f); */
  /* test_invite_request(c1, c2, f); */

  /* test_list_update(c1, c2, f); */
  /* test_chat_message(c1, c2, f); */
  /* test_chat_ack(c1, c2, f); */

  /* auto u1 = user(addr, 6789, "Bob"); */
  /* c3.accept(); */

  /* u1.send("Sup"); */
  /* cerr << c3.receive() << "\n"; */
}

int main(int argc, char *argv[]) {
  if (argc < 2) { cerr << "Usage: ./test IP_ADDRESS\n"; }
  else { run(argv[1]); }
}
