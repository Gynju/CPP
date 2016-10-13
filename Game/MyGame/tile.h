#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>

class Tile: public QGraphicsPixmapItem
{
public:
    Tile(QGraphicsPixmapItem* parent=NULL);

private:
    QString owner;
    int northAttackSide;
    int southAttackSide;
    int westAttackSide;
    int eastAttackSide;

};

#endif // TILE_H
