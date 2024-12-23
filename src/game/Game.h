#ifndef GAME_H
#define GAME_H
// #pragma once

#include "../Field.h"
#include "../ShipManager.h"
#include "../skills/SkillManager.h"
#include "GameState.h"
#include "../players/Bot.h"
#include "../players/User.h"
#include "../observer/Subject.h"
#include "../observer/Observer.h"

#include <fstream>

class GameState;

class Game : public Subject
{	
	public: 
	virtual GameState& getGameState() = 0;
	virtual void placeShips() = 0;
	virtual void process() = 0;
	virtual void load() = 0;
	virtual void save() = 0;
	virtual void start() = 0;
	virtual bool isUserDefeated() = 0;
	virtual Player* getCurrentPlayer() = 0;
	virtual Player* getCurrentEnemy() = 0;

};

#endif