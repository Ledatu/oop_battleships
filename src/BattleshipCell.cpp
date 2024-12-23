#include "BattleshipCell.h"
#include <iostream>
BattleshipCell::BattleshipCell(Battleship *battleship)
{
	this->battleship = battleship;
	(this->state) = BattleshipCellState::Unbroken;
	this->isHead = false;
}

BattleshipCellState BattleshipCell::GetState()
{
	return state;
}

void BattleshipCell::SetState(BattleshipCellState state)
{
	this->state = state;
}

bool BattleshipCell::getIsHead()
{
	return this->isHead;
}

void BattleshipCell::setIsHead(bool i)
{
	this->isHead = i;
}
bool BattleshipCell::AttackBattleshipCell(int damage)
{
	auto start_state = state;
	state = (state - damage > 0) ? BattleshipCellState(state - damage) : BattleshipCellState::Destroyed;
	return (start_state != BattleshipCellState::Destroyed) ? isBattleshipDestroyed() : false;
}

bool BattleshipCell::isBattleshipDestroyed()
{
	return battleship->isDestroyed();
}
