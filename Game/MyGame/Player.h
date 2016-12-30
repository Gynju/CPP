#include "Tile.h"
#include "Unit.h"
#include "Building.h"
#include "Recruiting.h"

#ifndef PLAYER_H
#define PLAYER_H

class Player
{
public:
   Player(QString name, int food, int wood, int stone);

   QString Name;

   int resources[3];
   int resourcesIncome[3];

   QList<Unit *> unitList;
   QList<Tile *> tileList;

   QList<Building *> buildingList;
   QList<Recruiting *> recruitList;

   bool building = false;
   bool recruiting = false;

   int city_X;
   int city_Y;
   int cityListLocation;

   void update();
   void updateText();
   void updateIcons(int listPosition);
};

#endif // PLAYER_H
