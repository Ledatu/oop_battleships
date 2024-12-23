#ifndef SKILLVISITOR_H
#define SKILLVISITOR_H
#include <string>

class DoubleDamageFactory;
class ScanerFactory;
class ShellingFactory;

class SkillVisitor {
public:
	virtual std::string visit(ShellingFactory* creator) = 0;
	virtual std::string visit(DoubleDamageFactory* creator) = 0;
	virtual std::string visit(ScanerFactory* creator) = 0;
};

#endif