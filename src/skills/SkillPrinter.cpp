#include "SkillPrinter.h"

std::string  SkillPrinter::visit(ShellingFactory* creator)
{
	return "Shelling";
}

std::string SkillPrinter:: visit(DoubleDamageFactory* creator)
{
	return "DoubleDamage";
}


std::string SkillPrinter::visit(ScanerFactory* creator)
{
	return "Scaner";
}



