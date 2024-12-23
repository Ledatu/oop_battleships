#ifndef SKILL_H
#define SKILL_H
#include "../infoHolders/SkillResultInfoHolder.h"
#include <string>

class Skill {
	public:
	virtual SkillResultInfoHolder& use() = 0;
	// virtual ~Skill();
};

#endif
