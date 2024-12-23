#include "ShipManager.h"
#include <iostream>
#include <exception>

int ShipManager::GetNumberBattleships()
{
    return this->battleships.size();
}

Battleship &ShipManager::operator[](int n)
{
    return *battleships[n];
}

ShipManager::ShipManager() {}
ShipManager::ShipManager(std::vector<int> lengths)
{
    for (auto &length : lengths)
    {
        battleships.push_back(new Battleship(length));
    }
}

bool ShipManager::isDefeated()
{
    for (int i = 0; i < this->GetNumberBattleships(); i++)
    {
        if (!this->operator[](i).isDestroyed())
            return false;
    }
    return true;
}
