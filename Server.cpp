#include "Server.h"
string SocketIO::read(){
    char n=0;
    string s="";
    while(n!='\n'){
        recv(clientId, &n,sizeof(char),0);
        s+=n;
    }
    return s;
}
void SocketIO::write(string text){
    const char* c = text.c_str();
    send(clientId,c,strlen(c),0);
}
void SocketIO::write(float f){
    ostringstream of;
    of << f;
    string s(of.str());
    write(s);
}
void SocketIO::read(float* f) {
}

Server::Server(int port)throw (const char*):port(port){
//        this->port = port;
    stopp = false;
    int addrlen = sizeof(address);
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd < 0){
        throw "failed";
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    if((bind(fd, (struct sockaddr*)&address, addrlen)) < 0){
        throw "failed";
    }
    if(listen(fd,3) < 0){
        throw "failed";
    }
}
void sigHandler(int sigNum){
    cout << "done" << endl;
}


void Server::start(ClientHandler& ch)throw(const char*){
    t= new thread([&ch,this](){
        signal(SIGALRM,sigHandler);
        while (!stopp) {
            alarm(1);
            socklen_t clientSize=sizeof(user_addr);
            int user_fd = accept(fd, (struct sockaddr *) &user_addr, &clientSize);
            if (user_fd > 0) {
                SocketIO io(user_fd);
                ch.handle(&io);
                close(user_fd);
            }
            alarm(0);
        }
        close(fd);
    });
}

void Server::stop(){
    stopp = true;
    t->join(); // do not delete this!
}
//
Server::~Server() {
}

