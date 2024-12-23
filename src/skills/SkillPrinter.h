#ifndef SKILLPRINTER_H
#define SKILLPRINTER_H

#include "SkillVisitor.h"
#include <string>

class SkillPrinter : public SkillVisitor
{
	std::string visit(ShellingFactory *creator) override;
	std::string visit(DoubleDamageFactory *creator) override;
	std::string visit(ScanerFactory *creator) override;
};

#endif