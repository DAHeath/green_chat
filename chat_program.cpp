#include "client.hpp"

int joinRoom(uint64_t id, std::string){
}

int parseInput(std::string){

}

static void inputLoop(){
    
    while(true){
        exit_mut.lock();
        if(exit){
            return;
        }
        exit_mut.unlock();
        
        
    }
}

int main(int argc, char** argv){
    bool inRoom = false;
    std::string roomName "";
    uint64_t roomID = 0;
    std::Map<uint32_t,std::string> peerList;
    bool exit = false;
    
    std::mutex inRoom_mut;
    std::mutex peerList_mut;
    std::mutex exit_mut;
    
    
}