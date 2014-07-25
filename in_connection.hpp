#include <thread>
#include "client.hpp"
#include "list_update.hpp"

namespace inmessage {

  void run(client client_ob);

  void receive_messages(client client_ob);

  void updatelist(uint32_t flag, list_update body);

}