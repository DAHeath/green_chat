#include "socket.hpp"
#include "client.hpp"
#include "message.hpp"

#include <iostream>

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

  auto s = "1234567890101112131415";
  std::cerr << s << "\n";
  std::cerr << message::from_string(s).to_string() << "\n";
}
