#ifndef BOT_H
#define BOT_H

#include "Player.h"
#include "../infoHolders/commandHolder.h"
#include "../game/Game.h"
#include "../utils/Randomizer.h"

class Bot : public Player
{
private:
	Field field;
	ShipManager shipManager;
	std::vector<std::pair<int, int>> availableMoves;
	int damage;

public:
	Bot(int width, int height, std::vector<int> lengths);
	Bot(const Bot &other) : field(other.field), shipManager(other.shipManager), damage(other.damage) {};
	Bot &operator=(const Bot &other)
	{
		if (this != &other)
		{
			this->field = other.field;
			this->shipManager = other.shipManager;
			this->damage = other.damage;
		}
		return *this;
	}
	Bot();
	~Bot();
	Action move(Player &player) override;
	Field &getField() override;
	void placeShips() override;
	ShipManager &getShipManager() override;
};

#endif
