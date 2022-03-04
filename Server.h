

#ifndef FLIGHTGEAR_DETECTOR1_SERVER_H
#define FLIGHTGEAR_DETECTOR1_SERVER_H
#include <thread>
#include <sys/socket.h>
#include <netinet/in.h>
#include "commands.h"
#include "CLI.h"
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <pthread.h>
#include <sstream>
#include <stdio.h>
#include <string.h>
using namespace std;

//ClientHandler interface:


class SocketIO: public DefaultIO{
    int clientId;
public:
    SocketIO(int id):clientId(id){}
    virtual string read();
    virtual void write(string text);
    virtual void write(float f);
    virtual void read(float* f);
};
// you can add helper classes here and implement on the cpp file

class ClientHandler{
public:
    virtual void handle(SocketIO* io)=0;
};

// edit your AnomalyDetectionHandler class here
class AnomalyDetectionHandler:public ClientHandler{
public:
    virtual void handle(SocketIO* io){
        CLI cli(io);
        cli.start();
    }
};

void run(int fd, struct sockaddr_in user_addr, bool stop, ClientHandler* ch);
// implement on Server.cpp
class Server {
    thread* t; // the thread to run the start() method in
    //int clientLimit;
    int port;
    volatile bool stopp;
    struct sockaddr_in address;
    struct sockaddr_in user_addr;
    int fd;
    // you may add data members

public:
    Server(int port) throw (const char*);
    virtual ~Server();
    void start(ClientHandler& ch)throw(const char*);
    void stop();
};
#endif //FLIGHTGEAR_DETECTOR1_SERVER_H
