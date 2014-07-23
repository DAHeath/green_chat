#include "message_header.hpp"

#include <sstream>

#include "bit_ops.hpp"

#include <iostream>


using namespace std;

message_header *message_header::from_string(string s) {
  stringstream ss {s};
  auto type = bit::extract8(ss);
  auto flags = bit::extract8(ss);
  auto length = bit::extract16(ss);
  auto address = bit::extract32(ss);
  return new message_header { type, flags, length, address };
}

message_header::message_header(uint32_t t, uint32_t f, uint32_t l, uint32_t a) :
  type(t), flags(f), length(l), address(a) { }

string message_header::to_string() const {
  ostringstream ss;
  bit::insert8(ss, type);
  bit::insert8(ss, flags);
  bit::insert16(ss, length);
  bit::insert32(ss, address);
  return ss.str();
}
