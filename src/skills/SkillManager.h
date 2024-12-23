#ifndef SKILLMANAGER_H
#define SKILLMANAGER_H

#include <iostream>
#include <optional>
#include <string>
#include <queue>
#include "ShellingFactory.h"
#include "DoubleDamageFactory.h"
#include "ScanerFactory.h"
// #include "Skill.h"
// #include "SkillFactory.h"
#include "../infoHolders/SkillResultInfoHolder.h"
#include "../infoHolders/SkillInfoHolder.h"

#include "../exceptions/NoneAvailableSkillsException.h"


class SkillManager
{
	std::queue<SkillFactory*> skill_factory_queue;
	std::vector<SkillFactory*> pull_of_skills;
	public:
	SkillManager(std::optional<std::vector<SkillFactory*>> skill_factories= std::nullopt);
   	SkillFactory* operator[](int n);

	void update(SkillResultInfoHolder& skill_result);
	Skill* getSkill(SkillInfoHolder& skill_info);
	void addSkill(std::optional<SkillFactory*> skill = std::nullopt);
	void printAvailableSkills();
	int size();
	void pop();
};

#endif

