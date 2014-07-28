#include "client.hpp"

time_t timer;
client mainClient;
bool exit;
uint32_t myAddr;
message_factory factory;

std::mutex exit_mut;
std::mutex client_mut;

int joinRoom(uint64_t id, uint32_t addr, std::string name){
    auto newSocket = socket::connected(addr, 8000);
    std::string pot_name = name;
    newSocket.send(factory.build_invite_request(id, name).to_string());
    cout << "Joining room..." << endl;
    std::string response;
    message response_mess;
    while(!inRoom){ 
      response = newSocket.receive();
      if(response.length() > 0){
        response_mess = message::from_string(response);
        if(response_mess.header->type == message_type::LIST_UPDATE && !(response_mess->header.flags)) {
          roomID = response_mess.body->room_id();
          std::vector<uint32_t> addresses = response_mess.body->addresses();
          std::vector<std::string> names = response_mess.body->names();
          inRoom = true;
          
          for(int i = 0; i < addresses.length(); i++){
            mainClient.add_neighbor(
          }          
        }
      }
    };
}

int parseInput(std::string input){
    if(strcmp(input, "#leave") == 0
        mainClient.send(factory.build_remove_list_update(
            roomID, std::vector(1,myAddr), std::vector(1,username).to_string());
        return 0;
    }else{
        mainClient.send(factory.build_chat_message(
            roomID,time(&timer),input).to_string());
    }
}

static void inputLoop(){
    int ret_code;
    std::string input = "";
    std::string input_cpy = "";
    std::string token = "";
    std::string sec_token = "";
    uint64_t room_id;
    
    while(true){
        exit_mut.lock();
        if(exit){
            return;
        }
        exit_mut.unlock();
        
        //get user input
        getline(cin, input);
        input_cpy.assign(input);
        stringstream ss(input_cpy);
        getline(ss, token, ' ');
        
        //handle username changes
        if(strcmp(token, "#nick") == 0){
            mainClient.set_name(getline(ss, username, ' '));
            continue;
        }
        
        //handle exit commands
        if(strcmp(token, "#exit") == 0){
            exit_mut.lock();
            mainClient.send(factory.build_remove_list_update(
                roomID, std::vector(1,myAddr), std::vector(1,username)).to_string());
            exit = true;
            exit_mut.unlock();
            continue;
        }

        if(strcmp(token, "#room") == 0 && !mainClient.inRoom()){
          getline(ss, token, ' ');
          getline(ss, sec_token, ' ');
          std::istringstream other_ss(token);
          if(!(iss >> room_id)) { continue; }
          mainClient.set_room(room_id, sec_token);
          continue;
        }
        
        if(mainClient.inRoom()){
           ret_code = parseInput(input); 
        }else{
            //TODO: parse room addr and ID from input, call joinRoom
            uint32_t room_addr;
            bool failed = false;
            std::istringstream iss(token);

            if(!(iss >> room_id)){
              failed = true;
            }
            getline(ss,token,' ');
            room_addr = inet_addr(token);
            if(!failed){
              joinRoom(room_id, room_addr, input_cpy);
            }else{
              cout << "Usage is <room ID> <room-member IP address> <room name>" << endl;
            }
        }
    }
}

int main(int argc, char** argv){
    timer;
    exit = false;
    
    //get local host address
    char ac[80];
    gethostname(ac, sizeof(ac));
    struct hostent *phe = gethostbyname(ac);
    myAddr = phe->h_addr_list[0]->s_addr;
    
    mainClient("USER",myAddr,8000);
    factory(myAddr);
    
    std::thread userInput(inputLoop);
    inmessage::run(mainClient);
    connection_interface::run(mainClient);
    while(!exit) { };
    client.close_connections();
}
