#pragma once

#include <string.h>
#include <unordered_map>
// #include <invalid_argument>

#include "../ShipManager.h"
#include "../Field.h"
#include "../skills/SkillManager.h"

#include "../libs/json.hpp"
#include "../Commands.h"

class Deserialization
{
private:
    nlohmann::json &j;

public:
    Deserialization(nlohmann::json &j) : j(j) {};

    void from_json(ShipManager &shipManager, std::string key);
    void from_json(Field &field, std::string key);
    void from_json(SkillManager &abilityManager, std::string key);
    void from_json(std::unordered_map<char, Commands> &commands);
};