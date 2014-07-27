#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>

#include "socket.hpp"

class client {
  public:
    client(unsigned int addr, unsigned int socket) :
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
    network::socket move_to_comm(uint32_t ip_address, std::string name);

    void make_courier(network::socket newCourier);

    /**
    * Send the message to the one in couriers list
    */
    void sendtoOne(const std::string message);

    std::vector<uint32_t> getaddresses() { return addresses; }

    std::vector<std::string> getnames() { return names; }

    unsigned int ip_address() { return _ip_address; }

    void set_room(uint64_t room_id, std::string room_name) {
      _room_id = room_id;
      _room_name = room_name;
    }

    uint64_t room_id() { return _room_id; }
    std::string room_name() { return _room_name; }

  private:
    network::socket interface;
    unsigned int _ip_address;

    uint64_t _room_id;
    std::string _room_name;

    std::vector<network::socket> couriers;
    std::vector<network::socket> comm_sockets;
    std::vector<uint32_t> addresses;
    std::vector<std::string> names;
};

#endif
