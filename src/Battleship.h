#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <vector>
#include <memory>

#include "BattleshipCell.h"
class BattleshipCell;

enum Direction
{
	Up,
	Right,
	Down,
	Left
};

struct Position
{
	int x;
	int y;
	Position() : x(0), y(0) {};
	Position(int x, int y) : x(x), y(y) {};
};

class Battleship
{
public:
	Battleship(int length);
	void setDirection(Direction direcrion);
	Direction GetDirection();
	int GetLength();
	BattleshipCell &operator[](int index);
	bool isDestroyed();
	Position getPosition();
	void setPosition(Position pos);

private:
	Position position;
	std::vector<BattleshipCell> battleship;
	Direction direction;
};

#endif