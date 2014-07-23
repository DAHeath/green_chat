#include "socket.hpp"
#include "client.hpp"
#include "room_list.hpp"
#include "room_query.hpp"
#include "invite_request.hpp"
#include "list_update.hpp"
#include "chat_message.hpp"
#include "chat_ack.hpp"

#include "message.hpp"
#include "message_header.hpp"
#include "message_body.hpp"
#include "message_types.hpp"

#include "bit_ops.hpp"

#include <iostream>
#include <cstdint>
#include <assert.h>
#include <sstream>

using namespace std;

void test_room_query(client c1, client c2, uint32_t addr) {
  auto h = new message_header(message_type::ROOM_QUERY, 0, 0, addr);
  message m { h, new room_query() };

  c1.send(m.to_string());
  auto s = c2.receive();
  assert(m == message::from_string(s));
}

void test_room_list(client c1, client c2, uint32_t addr) {
  vector<uint64_t> ids { 0x1050, 0x1050105010501050 };
  vector<string> names { "ROOM1", "ROOM2" };
 
  message_body *body = new room_list(ids, names);
  auto h = new message_header(body->type(), 0, body->length(), addr);

  message m { h, body };
  c1.send(m.to_string());
  assert(m == message::from_string(c2.receive()));
}


void test_invite_request(client c1, client c2, uint32_t addr) {
  message_body *body = new invite_request(0x1050, "ROOM1");
  auto h = new message_header(body->type(), 0, body->length(), addr);
  message m { h, body };

  c1.send(m.to_string());
  assert(m == message::from_string(c2.receive()));
}


void test_list_update(client c1, client c2, uint32_t addr) {
  uint64_t room_id { 0x1050 };
  vector<uint32_t> addresses { 0x3333, 0x33333333 };
  vector<string> names { "User1", "Superdupername!" };

  message_body *body = new list_update(room_id, addresses, names);
  auto h = new message_header( body->type(), 0, body->length(), addr);

  message m { h, body };

  c1.send(m.to_string());
  assert(m == message::from_string(c2.receive()));
}

void test_chat_message(client c1, client c2, uint32_t addr) {
  uint64_t room_id { 0x1050 };
  uint32_t timestamp { 0x13231323 };
  string mes { "This is just a test message." };

  message_body *body = new chat_message(room_id, timestamp, mes);
  auto h = new message_header(body->type(), 0, body->length(), addr);

  message m { h, body };

  c1.send(m.to_string());
  assert(m == message::from_string(c2.receive()));
}

void test_chat_ack(client c1, client c2, uint32_t addr) {
  uint64_t room_id { 0x1050 };
  uint32_t timestamp { 0x13231323 };

  message_body *body = new chat_ack(room_id, timestamp);
  auto h = new message_header(body->type(), 0, body->length(), addr);

  message m { h, body };

  c1.send(m.to_string());
  assert(m == message::from_string(c2.receive()));
}

void run(string address) {
  uint32_t addr = network::interpret_address(address);

  auto c1 = client(4567);
  auto c2 = client(5678);

  c1.add_neighbor(addr, 5678);
  c2.accept();

  test_room_query(c1, c2, addr);
  test_room_list(c1, c2, addr);
  test_invite_request(c1, c2, addr);
  test_list_update(c1, c2, addr);
  test_chat_message(c1, c2, addr);
  test_chat_ack(c1, c2, addr);
}

int main(int argc, char *argv[]) {
  if (argc < 2) { cerr << "Usage: ./test IP_ADDRESS\n"; }
  else { run(argv[1]); }
}
