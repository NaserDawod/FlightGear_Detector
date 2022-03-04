

#ifndef FLIGHTGEAR_DETECTOR1_CLI_H
#define FLIGHTGEAR_DETECTOR1_CLI_H
#include <string.h>
#include "commands.h"

using namespace std;

class CLI {
    DefaultIO* dio;
    vector<Command*> commands;
    // you can add data members
public:
    CLI(DefaultIO* dio);
    void start();
    virtual ~CLI();
private:
    void printStart(){
        dio->write("Welcome to the Anomaly Detection Server.\n");
        dio->write("Please choose an option:\n");
        for(int i = 0; i < 6; ++i){
            dio->write(commands[i]->getdesc() + "\n");
        }
    }
};
#endif //FLIGHTGEAR_DETECTOR1_CLI_H
