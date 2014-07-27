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

    std::string receiveConnection();

    //TODO: add function for sending and handling invite_request

    /**
    *remove a connection
    */
    void remove_neighbor(uint32_t ip_address);


    network::socket move_to_comm(uint32_t ip_address, std::string name);

    void sendtoOne(const std::string message);

    std::vector<uint32_t> getaddresses() { return addresses};

    std::vector<std::string> getnames { return names};

  private:
    network::socket interface;
    std::vector<network::socket> couriers;
    std::vector<network::socket> comm_sockets;
    std::vector<uint32_t> addresses;
    std::vector<std::string> names;
};

#endif
