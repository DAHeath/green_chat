#ifndef SOCKET_HPP
#define SOCKET_HPP

#include <string>
#include "network.hpp"
#include <cstdint>

namespace network {

  class socket {
    public:
      /**
       * Create a socket that is bound to the given port. It can accept incoming
       * messages and create new ports via calls to accept. Up to queue_size
       * requests can be stored before they fall off. The queue is emptied
       * through calls to accept.
       */
      static socket bound(const int port, const int queue_size);

      /**
       * Creates a listening connected port. Because there is no outgoing IP
       * address, 
       */
      static socket connected(const uint32_t ip_address, const int port);

      void send(std::string message) const;
      std::string receive(const unsigned int length) const;
      void close() const;

      /**
       * Calls to accept should be reserved for bound sockets.
       */
      socket accept() const;

    private:
      static impl::socket_address build_address(const int port);
      static impl::socket_address build_address(
          const uint32_t ip_address, const int port);

      socket(const int _s) : s(_s) { };
      int s;

  };
};

#endif
