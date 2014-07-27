#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>

#include "socket.hpp"
#include "user.hpp"

class client {
  public:
    client(std::string name, unsigned int addr, unsigned int socket) :
      _name(name),
      interface(network::socket::bound(socket, 10)),
      _ip_address(addr) { }

    /**
     * Allows a client to establish a connection with another client who there
     * has yet to be any contact with. Bypasses the courier process.
     */
    void add_neighbor(uint32_t ip_address, std::string name, unsigned int socket);

    void accept();

    /**
     * Broadcast a message to every client who this client has successfully made
     * contact with.
     */
    void send(std::string message);

    /**
     * Get the first valid message received from contacts.
     */
    std::string receive();

    /**
    * Get the incoming connection message
    */
    std::string receiveConnection();

    //TODO: add function for sending and handling invite_request

    /**
    *remove a connection
    */
    void remove_neighbor(uint32_t ip_address);

    /**
    * Move the one in couriers list into the comm_list
    */
    void move_to_comm(uint32_t ip_address, std::string name);

    void make_courier(network::socket newCourier);

    /**
    * Send the message to the one in couriers list
    */
    void sendtoOne(const std::string message);

    unsigned int ip_address() { return _ip_address; }

    void set_room(uint64_t room_id, std::string room_name) {
      _room_id = room_id;
      _room_name = room_name;
    }

    std::string name() { return _name; }

    uint64_t room_id() { return _room_id; }
    std::string room_name() { return _room_name; }

  private:
    std::string _name;
    network::socket interface;
    unsigned int _ip_address;

    uint64_t _room_id;
    std::string _room_name;

    std::vector<network::socket> couriers;
    std::vector<user> comm_sockets;
};

#endif
