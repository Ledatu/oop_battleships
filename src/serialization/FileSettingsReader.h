#pragma once
#include <string>
#include <unordered_map>
#include "FileWrapper.h"
#include "../libs/json.hpp"
#include "../Commands.h"
#include "../gameController/InputHandler.h"
#include "Deserialization.h"

// std::string toString(Commands command)
// {
// 	switch(command)
// class InputHandler;

// }

class FileSettingsReader
{
	InputHandler &inputHandler;
	FileWrapper fileWrapper;

public:
	FileSettingsReader(InputHandler &inputHandler, std::string fileName) : inputHandler(inputHandler), fileWrapper(fileName) {};
	void deserializeCommands();
};