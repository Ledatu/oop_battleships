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
    int count = 4;
    for (auto &length : lengths)
    {   
        for (int i = 0; i < length; i++)
        {
            battleships.push_back(new Battleship(count));
        }
        count--;
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
