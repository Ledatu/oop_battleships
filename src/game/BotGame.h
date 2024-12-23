#ifndef BotGame_H
#define BotGame_H

#include <string>
#include <memory>
#include "Game.h"
#include "../players/User.h"
#include "../players/Bot.h"
#include "../players/Player.h"
#include "../observer/Observer.h"
#include "../observer/Subject.h"
#include "GameState.h"
#include "GameSaver.h"

class BotGame : public Game{

	User& user;
	Bot& bot;
	GameState& state;
	Player* currentPlayer;
	Player* currentEnemy;
	int& countMoves;
	int& countRounds;
	GameSaver gameSaver;

	public:
	BotGame(User& user, Bot& bot, GameState& state, std::string fileName): user(user), bot(bot), state(state), countMoves(state.getMoves()), countRounds(state.getRounds()), gameSaver(fileName){};
	// BotGame(int width, int height, int numLength4, int numLength3, int numLength2, int numLength1);
	void start () override;
	void placeShips() override;
	void process() override;
	void load()override;
	void save() override;
	bool isUserDefeated() override;
	bool isBotDefeated();
	void resetBot();
	Player* getCurrentPlayer() override;
	Player* getCurrentEnemy() override;



	GameState& getGameState() override;
};

#endif