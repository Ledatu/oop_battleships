#pragma once

#include <string>

#include "GameState.h"
#include "../serialization/FileWrapper.h"

class GameState;

class GameSaver
{
private:
	const std::string fileName;
public:
	GameSaver(std::string fileName) : fileName(fileName){}; 
	void save(const GameState& state);
	void load(GameState& state);

};

