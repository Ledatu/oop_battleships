#ifndef Shelling_H
#define Shelling_H

#include "Skill.h"
#include "../ShipManager.h"




class Shelling : public Skill{
	ShipManager* ship_manager;
	public:
	Shelling(ShipManager& ship_manager);
	SkillResultInfoHolder& use() override;
};

#endif