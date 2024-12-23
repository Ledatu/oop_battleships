#include "FileSettingsReader.h"

void FileSettingsReader::deserializeCommands()
{	
	nlohmann::json json;
	std::unordered_map<char, Commands> commands;
	fileWrapper.read(json);
	Deserialization(json).from_json(commands);
	inputHandler.setCommands(commands);
}
