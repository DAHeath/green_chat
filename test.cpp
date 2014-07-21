#include "socket.hpp"
#include "client.hpp"
#include "message_header.hpp"
#include "room_list.hpp"

#include <iostream>
#include <cstdint>

#include <assert.h>

#include <sstream>

int main() {
  /* auto c1 = client(4567); */
  /* auto c2 = client(5678); */
  /* auto c3 = client(6789); */

  /* c1.add_neighbor("192.168.1.131", 5678); */
  /* c1.add_neighbor("192.168.1.131", 6789); */
  /* c2.accept(); */
  /* c3.accept(); */

  /* c1.send("Greetings"); */
  /* std::cerr << c2.receive() << "\n"; */
  /* std::cerr << c3.receive() << "\n"; */

  /* c2.send("Yo"); */
  /* std::cerr << c1.receive() << "\n"; */

  std::string s = "12345678";
  auto h_rep = message_header::from_string(s).to_string();
  assert(s.compare(h_rep) == 0);


  auto m = message_header::from_string(s);
  std::vector<uint64_t> ids { 0x1050, 0x1050105010501050 };
  std::vector<std::string> names { "ROOM1", "ROOM2" };
  auto rl = room_list(m, ids, names);

  auto rep = rl.to_string();
  auto rl2 = room_list::from_string(rep);

  assert(rep == rl2.to_string());


}
