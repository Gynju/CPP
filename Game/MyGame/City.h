#ifndef CITY_H
#define CITY_H

#include <QGraphicsSceneMouseEvent>

class City
{
public:
   City();
   void mousePressEvent(QGraphicsSceneMouseEvent *event);
   void selectUnit();
   void checkHP();

   int hp;

   bool occupied;
   QString owner;

   QList<int> subjectedTilesLocation;

   int X;
   int Y;
   int listLocation;
   int playerListLocation;
};

#endif // CITY_H
