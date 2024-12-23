#pragma once
// #include "../game/GameState.h"
#include <string>

class GameState;

class Observer {
public:
    virtual ~Observer() = default;
    virtual void updateGameState(GameState& gameState) = 0;
	virtual void printMessage(std::string) = 0;
	virtual void printMessage(const char*) = 0;
	
};