#ifndef ROOM_LIST_HPP
#define ROOM_LIST_HPP

#include <vector>

#include "message_body.hpp"

class room_list : public message_body {
  public:
    static room_list *from_string(std::string);
    room_list(std::vector<uint64_t> ids, std::vector<std::string> names) :
      _ids(ids), _names(names) { }

    std::string to_string() const;

    std::vector<uint64_t> ids() const { return _ids; }
    std::vector<std::string> names() const { return _names; }

    uint32_t length() const;
    uint32_t type() const { return message_type::ROOM_LIST; }

    bool operator==(const room_list &other) {
      return ids()   == other.ids() &&
             names() == other.names();
    }
    bool operator!=(const room_list &other) { return !(*this==other); }
    bool operator==(const message_body &other) {
      return typeid(*this) == typeid(other) &&
        *this==dynamic_cast<const room_list&>(other);
    }

  private:
    std::vector<uint64_t> _ids;
    std::vector<std::string> _names;
};

#endif
