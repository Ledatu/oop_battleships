#include "Serialization.h"
#include <fstream>

void Serialization::to_json(ShipManager &shipManager, std::string key)
{
    nlohmann::json jsm = nlohmann::json{};

    for (int i = 0; i < shipManager.GetNumberBattleships(); i++)
    {
        Battleship &temp = shipManager[i];
        std::string key = "ship" + std::to_string(i);
        jsm[key] = {
            {"length", temp.GetLength()},
            {"direction", temp.GetDirection()},
            {"segments", nlohmann::json::array()},
            {"y", temp.getPosition().y},
            {"x", temp.getPosition().x}};

        for (int j = 0; j < temp.GetLength(); j++)
        {
            BattleshipCell &tempcell = temp[j];
            jsm[key]["segments"].push_back({{"State", tempcell.GetState()}});
        }
    }

    j[key] = jsm;
}

void Serialization::to_json(Field &field, std::string key)
{
    nlohmann::json jf = nlohmann::json{};

    jf["height"] = field.GetHeight();
    jf["width"] = field.GetWidth();

    for (int y = 0; y < field.GetHeight(); y++)
    {
        for (int x = 0; x < field.GetWidth(); x++)
        {
            std::string key = "cell" + std::to_string(y) + std::to_string(x);
            jf[key] = {
                {"x", x},
                {"y", y},
                {"state", field[y][x].GetFieldState()},
            };
        }
    }
    j[key] = jf;
}

void Serialization::to_json(SkillManager &skillManager, std::string key)
{
    nlohmann::json jam = nlohmann::json{};
    SkillPrinter sp;
    for (int i = 0; i < skillManager.size(); i++)
    {
        jam["abilities"].push_back(
            skillManager[i]->accept(&sp));
    }

    j[key] = jam;
}