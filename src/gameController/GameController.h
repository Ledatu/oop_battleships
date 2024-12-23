#pragma once

#include "../game/Game.h"
#include "../displayer/Output.h"
#include "../exceptions/ShipNearAnotherException.h"

template <typename Input, typename Displayer>
class GameController
{
	Game &game;
	Input &input;
	Output<Displayer> &output;

public:
	GameController(Game &game, Input &input, Output<Displayer> &output) : game(game), input(input), output(output) {};
	void run();
	void processUser();
	void placeShips();
};

template <typename Input, typename Displayer>
void GameController<Input, Displayer>::run()
{
	this->placeShips();
	while (!game.isUserDefeated())
	{
		auto user = &(game.getGameState().getUser());
		Player *currentPlayer = game.getCurrentPlayer();
		Player *currentEnemy = game.getCurrentEnemy();
		if (user == currentPlayer)
		{
			this->processUser();
			auto &gameState = this->game.getGameState();
			game.notifyObservers(gameState);
		}
		else
		{
			currentPlayer->move(*currentEnemy);
		}
	}
}
template <typename Input, typename Displayer>
void GameController<Input, Displayer>::processUser()
{
	Commands command = Commands::Info;
	bool flag = false;
	std::pair<int, int> coords;
	while (command != Commands::Quit)
	{
		command = input.processCommandInput();
		switch (command)
		{
		case Commands::UseAttack:
			coords = input.processCoordinateInput();
			this->game.getGameState().getUser().attack(*game.getCurrentEnemy(), coords.first, coords.second);
			flag = true;
			break;
		case Commands::UseSave:
			this->game.save();
			break;
		case Commands::UseSkill:
			this->game.getGameState().getUser().useSkill(*game.getCurrentEnemy());
			break;
		case Commands::UseLoad:
			this->game.load();
			break;
		default:
			output.printMessage("Unknown Command!");
		}
		if (flag)
			return;
	}
}

template <typename Input, typename Displayer>
void GameController<Input, Displayer>::placeShips()
{
	try
	{
		this->game.getGameState().getBot().placeShips();
	}
	catch (ShipNearAnotherException &e)
	{
		this->output.printMessage(e.what());
		return;
	}
	auto &user = this->game.getGameState().getUser();
	auto numShips = this->game.getGameState().getUser().getShipManager().GetNumberBattleships();

	for (size_t i = 0; i < numShips; i++)
	{
		this->game.notifyObservers(this->game.getGameState());
		this->output.printMessage("Введите координаты:");
		auto coords = this->input.processCoordinateInput();
		this->output.printMessage("Введите направление");
		Commands command = this->input.processCommandInput();
		std::cout << command << '\n'
				  << char(Commands::SetUp) << '\n';
		Direction direction;
		bool unknownDirection = false;
		switch (command)
		{
		case Commands::SetUp:
			direction = Direction::Up;
			break;
		case Commands::SetDown:
			direction = Direction::Down;
			break;
		case Commands::SetRight:
			direction = Direction::Right;
			break;
		case Commands::SetLeft:
			direction = Direction::Left;
			break;
		default:
			this->output.printMessage("Unknown Direction!");
			unknownDirection = true;
			break;
		}
		if (unknownDirection)
		{
			i--;
			continue;
		}
		try
		{
			user.placeShip(i, coords, direction);
		}
		catch (ShipNearAnotherException &e)
		{
			this->output.printMessage(e.what());
			i--;
			continue;
		}
	}
}