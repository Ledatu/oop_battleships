#ifndef SHIPMANAGER_H
#define SHIPMANAGER_H
#include <vector>
#include "Battleship.h"

class ShipManager
{
public:
   Battleship &GetBattleship();
   Battleship &operator[](int n);
   ShipManager();
   ShipManager(std::vector<int> lengths);
   int GetNumberBattleships();
   bool isDefeated();

private:
   std::vector<Battleship *> battleships;
};

#endif