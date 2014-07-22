#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <vector>

#include "socket.hpp"

class client {
  public:
    client(unsigned int socket) : interface(network::socket::bound(socket, 10)) { }

    /**
     * Allows a client to establish a connection with another client who there
     * has yet to be any contact with. Bypasses the courier process.
     */
    void add_neighbor(uint32_t ip_address, unsigned int socket);

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
  private:
    network::socket interface;
    std::vector<network::socket> couriers;
    std::vector<network::socket> comm_sockets;
};

#endif
