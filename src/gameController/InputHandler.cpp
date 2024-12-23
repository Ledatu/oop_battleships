#include "InputHandler.h"

InputHandler::InputHandler()
{
    this->commands = {
        {'a', Commands(0)},
        {'e', Commands(1)},
        {'q', Commands(2)},
        {'s', Commands(3)},
        {'p', Commands(4)},
        {'y', Commands(5)},
        {'n', Commands(6)},
        {'u', Commands(7)},
        {'l', Commands(8)},
        {'r', Commands(9)},
        {'d', Commands(10)},
        {'i', Commands(11)}};
}

void InputHandler::setCommands(std::unordered_map<char, Commands> commands)
{
    this->commands = commands;
}

Commands InputHandler::processCommandInput()
{
    std::string line;
    std::cin >> line;
    if (line.size() == 1 && this->commands.find(line[0]) != this->commands.end())
    {
        return this->commands[line[0]];
    }
    return Commands(11);
    // throw std::exception("Unkown command");
}

std::pair<int, int> InputHandler::processCoordinateInput()
{
    int x, y;
    while (true)
    {
        std::cin >> x >> y;
        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        break;
    }
    return std::pair{x, y};
}
