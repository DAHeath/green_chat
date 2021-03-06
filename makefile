CXXFLAGS := -g -Wall -std=c++11 -lm
CXX=g++
MY_OBJECTS= network.o socket.o client.o message_header.o room_list.o room_query.o invite_request.o list_update.o bit_ops.o chat_message.o chat_ack.o message.o connection_thread.o

all: test

test: $(MY_OBJECTS) test.o
	$(CXX) -o test test.o $(MY_OBJECTS)

clean:
	rm -f test *.o
