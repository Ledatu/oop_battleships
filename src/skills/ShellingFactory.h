#ifndef ShellingFACTORY_H
#define ShellingFACTORY_H
#include "SkillFactory.h"
#include "Shelling.h"

class SkillVisitor;

class ShellingFactory : public SkillFactory
{
public:
	Skill *createSkill(SkillInfoHolder *skill_holder) override;
	std::string accept(SkillVisitor *visitor) override;
};

#endif