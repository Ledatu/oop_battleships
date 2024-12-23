#include "ShellingFactory.h"

Skill *ShellingFactory::createSkill(SkillInfoHolder* skill_holder)
{
	return new Shelling(skill_holder->getShipManager());
}

std::string ShellingFactory::accept(SkillVisitor* visitor)
{
	return visitor->visit(this);
}


