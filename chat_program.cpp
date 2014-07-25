#include "client.hpp"

bool inRoom;
time_t timer;
std::string roomName;
std::string username;
uint64_t roomID;
std::Map<uint32_t,std::Pair<std::string,int>> peerList;
client mainClient(8000);
bool exit;
uint32_t myAddr;
message_factory factory;
    
std::mutex inRoom_mut;
std::mutex peerList_mut;
std::mutex exit_mut;
std::mutex username_mut;

int joinRoom(uint64_t id, std::string){
    //TODO: create connection to input addr, send invite_request
}

int parseInput(std::string input){
    if(strcmp(input, "#leave") == 0
        inRoom_mut.lock();
        mainClient.send(factory.build_remove_list_update(
            roomID, std::vector(1,myAddr), std::vector(1,username).to_string());
        inRoom = false;
        inRoom_mut.unlock();
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
            username_mut.lock();
            getline(ss, username, ' ');
            username_mut.unlock();
            continue;
        }
        
        //handle exit commands
        if(strcmp(token, "#exit") == 0){
            inRoom_mut.lock();
            exit_mut.lock();
            mainClient.send(factory.build_remove_list_update(
                roomID, std::vector(1,myAddr), std::vector(1,username)).to_string());
            inRoom = false;
            exit = true;
            inRoom_mut.unlock();
            exit_mut.unlock();
        }
        
        inRoom_mut.lock();
        if(inRoom){
           ret_code = parseInput(input); 
        }else{
            //TODO: parse room addr and ID from input, call joinRoom
        }
    }
}

int main(int argc, char** argv){
    inRoom = false;
    timer;
    roomName = "";
    username = "USER";
    roomID = 0;
    peerList = new Map<uint32_t,std::Pair<std::string, int>>;
    exit = false;
    
    //get local host address
    char ac[80];
    gethostname(ac, sizeof(ac));
    struct hostent *phe = gethostbyname(ac);
    myAddr = phe->h_addr_list[0]->s_addr;
    
    factory = message_factory(myAddr);
    
    std::thread userInput(inputLoop);
    inmessage::run(mainClient);
    connection_interface::run(mainClient);
}