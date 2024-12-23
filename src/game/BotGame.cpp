#include "BotGame.h"

void BotGame::start()
{
	this->placeShips();
	this->process();
}

void BotGame::placeShips()
{
	this->bot.placeShips();
	this->user.placeShips();
}

void BotGame::process()
{
	while (!this->user.getShipManager().isDefeated())
	{
		auto state = this->getGameState();
		std::cout << state << '\n';
		if (countMoves % 2)
		{
			this->currentPlayer = &user;
			this->currentEnemy = &bot;
		}
		else
		{
			this->currentPlayer = &bot;
			this->currentEnemy = &user;
		}

		try
		{
			auto action = this->currentPlayer->move(*(this->currentEnemy));
			if (action == Action::Save)
			{
				this->save();
				continue;
			}
			if (action == Action::Load)
			{
				this->load();
				auto state = this->getGameState();
				std::cout << state;
				std::cout << "Игра была успешно загружена!";
				continue;
			}
		}
		catch (std::exception &error)
		{
			countMoves--;
			std::cout << error.what();
		}
		if (this->bot.getShipManager().isDefeated())
		{
			auto field = this->bot.getField();
			auto sm = this->bot.getShipManager();
			std::vector<int> shipLengths;
			for (int i = 0; i < sm.GetNumberBattleships(); i++)
			{
				shipLengths.push_back(sm[i].GetLength());
			}
			this->bot = Bot(field.GetWidth(), field.GetHeight(), shipLengths);
			this->state.getBot() = this->bot;
			this->bot.placeShips();
			this->countRounds++;
		}
		countMoves++;
	}
	// std::cout << "you lose:(\n";
}

GameState &BotGame::getGameState()
{
	return this->state;
}

void BotGame::load()
{
	try
	{
		gameSaver.load(state);
	}
	catch (nlohmann::json::exception &e)
	{
		std::cerr << "Error parsing JSON: " << e.what() << std::endl;
		return;
	}

	// }
}

void BotGame::save()
{
	gameSaver.save(state);
}

bool BotGame::isUserDefeated()
{
	return this->user.getShipManager().isDefeated();
}

void BotGame::resetBot()
{
	auto field = this->bot.getField();
	auto sm = this->bot.getShipManager();

	std::vector<int> shipLengths;
	for (int i = 0; i < sm.GetNumberBattleships(); i++)
	{
		shipLengths.push_back(sm[i].GetLength());
	}

	this->bot = Bot(field.GetWidth(), field.GetHeight(), shipLengths);
	this->state.getBot() = this->bot;
	this->bot.placeShips();
	this->countRounds++;
}

bool BotGame::isBotDefeated()
{
	return this->bot.getShipManager().isDefeated();
}

Player *BotGame::getCurrentPlayer()
{
	if (countMoves % 2)
	{
		return &user;
	}
	return &bot;
}
Player *BotGame::getCurrentEnemy()
{
	if (!(countMoves % 2))
	{
		return &user;
	}
	return &bot;
}
// void BotGame::move(int x, int y, bool isUseAbility)
// {
// 	if (isUseAbility)
// 	{
// 		state->useSkill();
// 	}
// 	auto coords = CoordHolder();
// 	coords.read();
// 	auto coord = coords.getCoords();
// 	state->attack(coord.first, coord.second);
// 	this->countMoves += 1;
// 	state = this->stateFactory->getState();
// }

// Field& BotGame::getPlayerField (){
// 	return playerField;
// }
// Field& BotGame::getEnemyField(){
// 	return enemyField;
// }

// ShipManager& BotGame:: getPlayerShipManager()
// {
// 	return playerShipManager;
// }

// ShipManager& BotGame::getEnemyShipManager()
// {
// 	return enemyShipManager;
// }

// GameState& BotGame::getGameState(){
// 	return *state;
// }

// SkillManager& BotGame::getSkillManager()
// {
// 	return skillManager;
// }
