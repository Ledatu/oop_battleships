#include "ConsoleDisplayer.h"

void ConsoleDisplayer::printSkillManager(SkillManager &skillManager)
{
	auto skillVisitor = SkillPrinter();
	if (skillManager.size() == 0)
	{
		std::cout << "Отсутсвуют\n";
	}
	for (int i = 0; i < skillManager.size(); i++)
	{
		auto str = skillManager[i]->accept(&skillVisitor);
		std::cout << i + 1 << ". " << str << '\n';
	}
}

void ConsoleDisplayer::printField(Field &field)
{
	size_t width = field.GetWidth();
	size_t height = field.GetHeight();

	// Header row with column labels (A, B, C, ...)
	std::cout << "   "; // Indent for row labels
	for (size_t x = 0; x < width; x++)
	{
		std::cout << x << " ";
	}
	std::cout << "\n";

	// Grid content
	for (size_t y = 0; y < height; y++)
	{
		// Row label (1, 2, ...)
		std::cout << std::setw(2) << y << " ";

		for (size_t x = 0; x < width; x++)
		{
			// Convert cell state to string
			std::string cell = fieldCellToString(field[y][x].GetFieldState());
			std::cout << cell << "";
		}
		std::cout << "\n"; // End of row
	}
}

std::string ConsoleDisplayer::fieldCellToString(FieldCellState state)
{
	// Simple cell representations
	switch (state)
	{
	case FieldCellState::Unknown:
		return "⬜"; // Empty cell
	case FieldCellState::Empty:
		return "⚪"; // Missed shot
	case FieldCellState::Ship2:
		return "🟩"; // Ship segment
	case FieldCellState::Ship1:
		return "🟨"; // Hit ship
	default:
		return "🟥"; // Destroyed ship
	}
}

void ConsoleDisplayer::printBreak(const std::vector<size_t> &widths)
{
	const size_t margin = 1;
	std::cout << '+';
	int counter = 0;
	for (size_t w : widths)
	{
		if (counter == 0)
		{
			std::cout << std::string(w + 1, '-') << '+';
		}
		else
		{

			std::cout << std::string(w, '-') << '+';
		}
		counter += 1;
	}
	std::cout << '\n';
}

void ConsoleDisplayer::printRow(const std::vector<std::string> &row, const std::vector<size_t> &widths)
{
	std::cout << '|';
	const size_t margin = 1;
	for (size_t i = 0; i < row.size(); i++)
	{
		size_t emojiWidth = !(row[i].find("🟦") != std::string::npos || row[i].find("🌀") != std::string::npos || row[i].find("🟩") != std::string::npos || row[i].find("🟨") != std::string::npos || row[i].find("🟥") != std::string::npos) ? 2 : 0;
		auto symbol = (row[i].length() > 1 && emojiWidth == 2) ? "|" : " |";
		std::cout << ' ' << std::setw(widths[i] - emojiWidth) << row[i] << symbol;
	}
	std::cout << '\n';
}

void ConsoleDisplayer::printStart()
{
	std::cout << R"(
                      __/___            
            _____/______|           
    _______/_____\_______\_____     
    \              < < <       |    
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
██████   █████  ████████ ████████ ██      ███████ ███████ ██   ██ ██ ██████      ██     ██  █████  ██████  
██   ██ ██   ██    ██       ██    ██      ██      ██      ██   ██ ██ ██   ██     ██     ██ ██   ██ ██   ██ 
██████  ███████    ██       ██    ██      █████   ███████ ███████ ██ ██████      ██  █  ██ ███████ ██████  
██   ██ ██   ██    ██       ██    ██      ██           ██ ██   ██ ██ ██          ██ ███ ██ ██   ██ ██   ██ 
██████  ██   ██    ██       ██    ███████ ███████ ███████ ██   ██ ██ ██           ███ ███  ██   ██ ██   ██ )"
			  << "\n\n";
}
void ConsoleDisplayer::printError(std::exception &e)
{
	std::cerr << e.what() << '\n';
}
void ConsoleDisplayer::printString(std::string message)
{
	std::cout << message << '\n';
}

void ConsoleDisplayer::printString(const char *message)
{
	std::cout << message << '\n';
}
