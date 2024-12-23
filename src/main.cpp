#include "game/BotGame.h"
#include <iostream>
#include "gameController/GameController.h"
#include "gameController/InputHandler.h"
#include "displayer/Output.h"
#include "displayer/ConsoleDisplayer.h"
#include "serialization/FileSettingsReader.h"

int main()
{
    auto bot = Bot(10, 10, {1, 2, 3, 4});
    auto user = User(10, 10, {1, 2, 3, 4});

    int countr = 1;
    int countm = 1;
    auto state = GameState(user, bot, countr, countm);
    std::string filename = "/Users/kirillverdin/Downloads/oop_battleships/commands.json";
    std::string settingsFileName = "/Users/kirillverdin/Downloads/oop_battleships/commands.json";
    ConsoleDisplayer displayer;
    auto output = Output<ConsoleDisplayer>(displayer);
    InputHandler input;
    auto reader = FileSettingsReader(input, settingsFileName);
    try
    {
        reader.deserializeCommands();
    }
    catch (std::invalid_argument &e)
    {
        output.printMessage(e.what());
    }
    std::shared_ptr<Observer> obs = std::make_shared<Output<ConsoleDisplayer>>(output);
    auto game = BotGame(user, bot, state, filename);
    game.addObserver(obs);
    auto gameController = GameController<InputHandler, ConsoleDisplayer>(game, input, output);
    gameController.run();

    return 0;
}