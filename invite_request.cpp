#include "invite_request.hpp"

#include "bit_ops.hpp"
#include "message_types.hpp"

using namespace std;

invite_request *invite_request::from_string(string body) {
  auto id = bit::extract64(body);
  body = body.substr(8);
  unsigned int divide = body.find('\0') + 1;
  auto room_name = body.substr(0, divide-1);

  body = body.substr(divide);

  divide = body.find('\0') + 1;
  auto user_name = body.substr(divide);
  user_name = user_name.substr(0, user_name.size()-1);

  return new invite_request { id, room_name, user_name };
}

string invite_request::to_string() const {
  ostringstream ss;
  bit::insert64(ss, _id);
  ss << _room_name << '\0';
  ss << _user_name << '\0';
  return ss.str();
}
