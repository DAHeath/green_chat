#ifndef CONNECTION_THREAD_HPP
#define CONNECTION_THREAD_HPP

#include <thread>

#include "client.hpp"
#include "message_factory.hpp"

class connection_thread {
  public:
    connection_thread(client c);
    void run();

  private:
    void process_messages();

    void respond_to_invite(message &m);
    void send_room_list();
    void send_names_list_to_new_user();
    void send_new_user_to_room(user u);
    void move_user_to_room(user u);

    client _c;
    message_factory _f;
};

namespace connection_interface {

  void run(client client_ob);

  void receive_connection(client client_ob);

}

#endif
