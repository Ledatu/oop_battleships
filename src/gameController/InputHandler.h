#pragma once

#include <unordered_map>
#include <string>
#include <iostream>
#include <exception>
#include "../Commands.h"

class InputHandler {
    private:
        std::unordered_map <char, Commands> commands;
    public:
        InputHandler();
        void setCommands(std::unordered_map <char, Commands> commands);
        Commands processCommandInput();
        std::pair<int, int> processCoordinateInput();
};