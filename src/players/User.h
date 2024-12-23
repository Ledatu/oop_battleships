#ifndef USER_H
#define USER_H

#include "Player.h"
#include "../infoHolders/commandHolder.h"
#include "../infoHolders/directionHolder.h"
#include "../skills/SkillManager.h"
#include <iostream>

class User : public Player
{
private:
	Field field;
	ShipManager shipManager;
	SkillManager skillManager;
	int damage;

public:
	int getDamage();
	User(int width, int height, std::vector<int> lengths);
	~User();
	User(const User &other)
		: shipManager(other.shipManager), field(other.field), skillManager(other.skillManager), damage(other.damage) {};
	User &operator=(User &other)
	{
		if (this != &other)
		{
			this->shipManager = other.shipManager;
			this->skillManager = other.skillManager;
			this->field = other.field;
			this->damage = other.damage;
		}
		return *this;
	}
	User();
	Action move(Player &player) override;
	void placeShips() override;
	void placeShip(int index, std::pair<int, int> coords, Direction direction);

	bool attack(Player &player, int x, int y);
	bool useSkill(Player &player);
	Field &getField() override;
	ShipManager &getShipManager() override;
	SkillManager &getSkillManager();
};

#endif
