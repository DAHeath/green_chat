#include "connection_thread.hpp"
#include "socket.hpp"


namespace connection_interface {

  void run(client client_ob) {
    std::thread t1(receive_connection, client_ob);
  }

  void receive_connection(client client_ob) {

  }

}
