#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include <vector>
#include <string>
#include "System.h"

class Input
{
    private:
        std::vector<std::string> input;
        std::vector<std::vector<std::string> > inputhandler;
        System* s;
    public:
        Input(System* _s);
        void getInput();
        void inputDivider();
        void checkCommand();
        void putCommands(std::vector<std::string> &line);
        void postCommands(std::vector<std::string> &line);
        void getCommands(std::vector<std::string> &line);
        void deleteCommands(std::vector<std::string> &line);
};

#endif
