#ifndef PLAYER_H
#define PLAYER_H

#include "Building.h"
#include "City.h"
#include "Recruiting.h"
#include "Tile.h"
#include "Unit.h"

class Player
{
public:
   Player(QString name, int food, int wood, int stone);
   void update();
   void updateIcons(int list_position);
   void updateText();

   int city_list_location;
   int city_X;
   int city_Y;
   int list_location;
   int resources[3];
   int resources_income[3];

   bool building = false;
   bool recruiting = false;

   QList<Unit *> unit_list;
   QList<Tile *> tile_list;
   QList<Building *> building_list;
   QList<Recruiting *> recruit_list;

   QString Name;
};

#endif // PLAYER_H
