#include "Battleship.h"
#include <iostream>

Battleship::Battleship(int length)
{
	this->battleship = std::vector<BattleshipCell>(length, BattleshipCell(this));
	this->battleship[0].setIsHead(true);
}

BattleshipCell &Battleship::operator[](int index)
{
	return battleship[index];
}

Direction Battleship::GetDirection()
{
	return this->direction;
}

int Battleship::GetLength()
{
	return battleship.size();
}

bool Battleship::isDestroyed()
{
	for (int i = 0; i < this->GetLength(); i++)
	{
		if (battleship[i].GetState() != BattleshipCellState::Destroyed)
			return false;
	}
	return true;
}

Position Battleship::getPosition() { return position; }
void Battleship::setPosition(Position pos) { position = pos; }
void Battleship::setDirection(Direction dir) { direction = dir; }