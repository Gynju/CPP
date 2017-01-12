#ifndef CITY_H
#define CITY_H

#include <QGraphicsSceneMouseEvent>

class City
{
public:
   City();
   void checkHP();
   void mousePressEvent(QGraphicsSceneMouseEvent *);
   void selectUnit();

   int hp;
   int list_location;
   int player_list_location;
   int X;
   int Y;

   bool occupied;

   QString owner;
   QList<int> subjected_tiles_location;

};

#endif // CITY_H
