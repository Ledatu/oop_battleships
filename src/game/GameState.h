#pragma once
#include "../skills/SkillPrinter.h"
#include "../players/Bot.h"
#include "../players/User.h"
#include "../serialization/FileWrapper.h"
#include "../libs/json.hpp"
#include "../serialization/Serialization.h"
#include "../serialization/Deserialization.h"
#include "../exceptions/ModifiedJsonException.h"
#include "GameSaver.h"
class Bot;
class User;

class GameState
{
	Bot &bot;
	User &user;
	int &countRounds;
	int &countMoves;

public:
	GameState(User &user, Bot &bot, int &countRounds, int &countMoves) : user(user), bot(bot), countRounds(countRounds), countMoves(countMoves) {};
	Bot &getBot();
	User &getUser();
	int &getRounds();
	int &getMoves();
	std::string getHash(std::string data);
	friend std::ostream &operator<<(std::ostream &os, GameState &game);
	friend FileWrapper &operator<<(FileWrapper &fileWrapper, GameState &state);
	friend FileWrapper &operator>>(FileWrapper &fileWrapper, GameState &state);
	GameState &loadGame(const std::string fileName);
	void saveGame(const std::string fileName);
};