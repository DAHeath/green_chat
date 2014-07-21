#include "message.hpp"

#include <sstream>

#include "bit_ops.hpp"

using namespace std;

message message::from_string(string s) {
  stringstream ss {s};
  auto type = bit::extract8(ss);
  auto flags = bit::extract8(ss);
  auto length = bit::extract16(ss);
  auto address = bit::extract32(ss);
  auto data = s.substr(8);
  return message { type, flags, length, address, data };
}

message::message( int t, int f, int l, int a, string d) :
  type(t), flags(f), length(l), address(a), data(d) { }

string message::to_string() {
  ostringstream ss;
  bit::insert8(ss, type);
  bit::insert8(ss, flags);
  bit::insert16(ss, length);
  bit::insert32(ss, address);
  ss << data;
  return ss.str();
}
