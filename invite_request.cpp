#include "invite_request.hpp"

#include "bit_ops.hpp"
#include "message_types.hpp"

using namespace std;

invite_request *invite_request::from_string(string body) {
  auto id = bit::extract64(body);
  auto name = body.substr(8);
  name = name.substr(0, name.size());

  return new invite_request { id, name };
}

string invite_request::to_string() const {
  ostringstream ss;
  bit::insert64(ss, _id);
  ss << _name << "\0";
  return ss.str();
}
