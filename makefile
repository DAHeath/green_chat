CXXFLAGS := -g -Wall -std=c++11 -lm
CXX=g++
MY_OBJECTS= network.o socket.o client.o message_header.o room_list.o bit_ops.o

all: test

test: $(MY_OBJECTS) test.o
	$(CXX) -o test test.o $(MY_OBJECTS)

clean:
	rm -f test *.o
