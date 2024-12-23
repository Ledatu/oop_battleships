#include "Deserialization.h"

void Deserialization::from_json(ShipManager &shipManager, std::string key)
{
    const auto &jsm = j.at(key);
    std::vector<int> shipLengths;

    for (const auto &jship : jsm)
    {
        auto length = jship.at("length");
        shipLengths.push_back(length);
    }
    shipManager = ShipManager(shipLengths);

    for (size_t i = 0; i < shipManager.GetNumberBattleships(); i++)
    {
        std::string key = "ship" + std::to_string(i);
        Battleship &ship = shipManager[i];
        ship.setDirection(Direction(jsm.at(key).at("direction")));
        int x = (int(jsm.at(key).at("x")));
        int y = (int(jsm.at(key).at("x")));
        ship.setPosition({x, y});
        auto segments = jsm.at(key).at("segments");
        auto it = segments.begin();
        for (int j = 0; j < ship.GetLength() && it < segments.end(); j++, ++it)
        {
            BattleshipCell &segment = ship[j];
            auto segmentJson = it.value();
            segment.SetState(BattleshipCellState(segmentJson.at("State")));
        }
    }
}

void Deserialization::from_json(Field &field, std::string key)
{
    const auto &jf = j.at(key);
    field = Field(jf.at("width"), jf.at("height"));

    for (int y = 0; y < field.GetHeight(); y++)
    {
        for (int x = 0; x < field.GetWidth(); x++)
        {
            std::string key = "cell" + std::to_string(y) + std::to_string(x);
            FieldCell &cell = field[y][x];
            cell.setIdBattleship(jf.at(key).at("idBattleShip"));
            cell.SetFieldCellState(FieldCellState(jf.at(key).at("state")));
            cell.setIsHead(jf.at(key).at("isHead"));
        }
    }
}

void Deserialization::from_json(SkillManager &skillManager, std::string key)
{
    const auto &jam = j.at(key);
    skillManager = SkillManager();
    skillManager.pop();
    skillManager.pop();
    skillManager.pop();
    for (const auto &jability : jam.at("abilities"))
    {
        if (jability == "DoubleDamage")
        {
            skillManager.addSkill(new DoubleDamageFactory());
        }
        else if (jability == "Scaner")
        {
            skillManager.addSkill(new ScanerFactory());
        }
        else if (jability == "Shelling")
        {
            skillManager.addSkill(new ShellingFactory());
        }
    }
}

void Deserialization::from_json(std::unordered_map<char, Commands> &commands)
{
    const auto &jsonCommands = j.at("commands");
    for (const auto pair : jsonCommands.items())
    {
        std::string i = pair.key();
        std::cout << i << '\t';
        std::string val = pair.value();
        char ch = val[0];
        // std::cout << Commands(i[0] - '0') << '\t';
        commands.insert({ch, Commands(atoi(i.c_str()))});
        if (commands.count(ch) != 1)
        {
            throw std::invalid_argument("Keys for commands must be unique!");
        }
    }
    std::cout << commands.size();
    if (commands.size() != 12)
    {
        throw std::invalid_argument("Number of commands must be 12");
    }
}
