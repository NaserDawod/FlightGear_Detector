#include "CLI.h"
CLI::CLI(DefaultIO* dio){
    this->dio = dio;
    commands.push_back(new fileCommand(dio));
    commands.push_back(new setAlgCommand(dio));
    commands.push_back(new detectCommand(dio));
    commands.push_back(new resultsCommand(dio));
    commands.push_back(new analyzeCommand(dio));
    commands.push_back(new exitCommand(dio));
}

void CLI::start(){
    Info info;
    int index=-1;
    while(index!=5){
        printStart();
        string input = dio->read();
        index=input[0]-'0'-1;
        if(index>=0 && index<=6)
            commands[index]->execute(&info);
    }
}

CLI::~CLI() {
    for(size_t i=0;i<commands.size();i++){
        delete commands[i];
    }
}


