#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <vector>

#include "socket.hpp"
#include "user.hpp"
#include "message.hpp"
#include "message_factory.hpp"

class client {
  public:
    client(std::string name, unsigned int addr, unsigned int socket) :
      _name(name),
      interface(network::socket::bound(socket, 10)),
      _ip_address(addr),
      _f(message_factory(addr)){ }

    void process_message(message &m);

    /**
     * Allows a client to establish a connection with another client who there
     * has yet to be any contact with. Bypasses the courier process.
     */
    void add_roommate(user u) { roommates.push_back(u); }
    void remove_roommate(uint32_t ip_address);
    void add_courier(network::socket s) { couriers.push_back(s); }
    void remove_courier(uint32_t address);

    /**
     * Broadcast a message to every client who this client has successfully made
     * contact with.
     */
    void send(std::string message);
    void send_to_courier(uint32_t address, std::string message);

    /**
     * Get the first valid message received from contacts.
     */
    std::string receive();
    void accept();
    /**
    * Get the incoming connection message
    */
    std::string receive_from_courier();

    unsigned int ip_address() { return _ip_address; }

    void set_room(uint64_t room_id, std::string room_name) {
      _room_id = room_id;
      _room_name = room_name;
    }

    std::string name() { return _name; }
    void set_name(std::string name) { _name = name; }

    uint64_t room_id() { return _room_id; }
    std::string room_name() { return _room_name; }
    bool in_room() { return _room_name != ""; }
    bool in_room(uint64_t room_id) { return _room_id == room_id; }

    void close_connections() {
      interface.close();
      for (auto s : couriers) s.close();
      for (auto u : roommates) u.close_connection();
    }

    bool has_roommate(uint32_t address, std::string name);


  private:
    void send_room_list(uint32_t address);
    void respond_to_invite(message &m);
    void send_names_list_to_new_user(user u);
    void send_new_user_to_room(user u);
    void move_user_to_room(user u);
    void respond_to_update(message &m);
    void add_appropriate_users(list_update *lu);

    network::socket courier_at(uint32_t address);

    std::string _name;
    network::socket interface;
    unsigned int _ip_address;

    message_factory _f;

    uint64_t _room_id;
    std::string _room_name;

    std::vector<network::socket> couriers;
    std::vector<user> roommates;
};

#endif
