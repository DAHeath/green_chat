#include "socket.hpp"
#include "client.hpp"
#include "message_header.hpp"
#include "room_list.hpp"
#include "room_query.hpp"
#include "invite_request.hpp"
#include "list_update.hpp"
#include "chat_message.hpp"
#include "chat_ack.hpp"

#include "bit_ops.hpp"

#include <iostream>
#include <cstdint>
#include <assert.h>
#include <sstream>

using namespace std;

void test_room_list(client c1, client c2, uint32_t addr) {
  vector<uint64_t> ids { 0x1050, 0x1050105010501050 };
  vector<string> names { "ROOM1", "ROOM2" };

  auto rl = room_list::from_data(addr, ids, names);
  c1.send(rl.to_string());
  assert(rl == room_list::from_string(c2.receive()));
}

void test_room_query(client c1, client c2, uint32_t addr) {
  auto rq = room_query::from_address(addr);
  c1.send(rq.to_string());
  assert(rq == room_query::from_string(c2.receive()));
}

void test_invite_request(client c1, client c2, uint32_t addr) {
  auto ir = invite_request::from_data(addr, 0x1050, "ROOM1");
  c1.send(ir.to_string());
  assert(ir == invite_request::from_string(c2.receive()));
}

void test_list_update(client c1, client c2, uint32_t addr) {
  uint64_t room_id { 0x1050 };
  vector<uint32_t> addresses { 0x3333, 0x33333333 };
  vector<string> names { "User1", "Superdupername!" };

  auto lu = list_update::from_data(true, addr, room_id, addresses, names);
  c1.send(lu.to_string());
  assert(lu == list_update::from_string(c2.receive()));
}

void test_chat_message(client c1, client c2, uint32_t addr) {
  uint64_t room_id { 0x1050 };
  uint32_t timestamp { 0x13231323 };
  string message { "This is just a test message." };

  auto cm = chat_message::from_data(addr, room_id, timestamp, message);
  c1.send(cm.to_string());
  assert(cm == chat_message::from_string(c2.receive()));
}

void test_chat_ack(client c1, client c2, uint32_t addr) {
  uint64_t room_id { 0x1050 };
  uint32_t timestamp { 0x13231323 };

  auto ca = chat_ack::from_data(addr, room_id, timestamp);
  c1.send(ca.to_string());
  assert(ca == chat_ack::from_string(c2.receive()));
}

void run(string address) {
  uint32_t addr = network::interpret_address(address);

  auto c1 = client(4567);
  auto c2 = client(5678);

  c1.add_neighbor(addr, 5678);
  c2.accept();

  test_room_list(c1, c2, addr);
  test_room_query(c1, c2, addr);
  test_invite_request(c1, c2, addr);
  test_list_update(c1, c2, addr);
  test_chat_message(c1, c2, addr);
  test_chat_ack(c1, c2, addr);
}

int main(int argc, char *argv[]) {
  if (argc < 2) { cerr << "Usage: ./test IP_ADDRESS\n"; }
  else { run(argv[1]); }
}
