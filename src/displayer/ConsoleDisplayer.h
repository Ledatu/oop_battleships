#pragma once
#include <iostream>
#include <vector>
#include <sstream>
#include <iomanip>
#include "../skills/SkillPrinter.h"
#include "../Field.h"
#include "../skills/SkillManager.h"

class ConsoleDisplayer {
	public:
	void printField(Field& field);
	void printSkillManager(SkillManager& skillManager);
	void printStart();
	void printError(std::exception& e);
	void printString(std::string message);
	void printString(const char* message);


	private:
	std::string fieldCellToString(FieldCellState state);
	void printBreak(const std::vector<size_t>& widths);
	void printRow(const std::vector<std::string>& row, const std::vector<size_t>& widths);
};