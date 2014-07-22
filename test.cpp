#include "socket.hpp"
#include "client.hpp"
#include "message_header.hpp"
#include "room_list.hpp"
#include "room_query.hpp"
#include "invite_request.hpp"

#include <iostream>
#include <cstdint>
#include <assert.h>
#include <sstream>

using namespace std;

void test_room_list(client c1, client c2, uint32_t addr) {
  vector<uint64_t> ids { 0x1050, 0x1050105010501050 };
  vector<string> names { "ROOM1", "ROOM2" };

  auto rl = room_list::from_data(addr, ids, names);
  auto s = rl.to_string();
  c1.send(s);
  assert(c2.receive() == s);
}

void test_room_query(client c1, client c2, uint32_t addr) {
  auto rq = room_query::from_address(addr);
  auto s = rq.to_string();
  c1.send(s);
  assert(c2.receive() == s);
}

void test_invite_request(client c1, client c2, uint32_t addr) {
  auto rq = invite_request::from_data(addr, 0x1050, "ROOM1");
  auto s = rq.to_string();
  c1.send(s);
  assert(c2.receive() == s);
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
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Usage: ./test IP_ADDRESS\n";
  }
  else {
    run(argv[1]);
  }
}
