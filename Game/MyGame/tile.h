#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include<QGraphicsSceneMouseEvent>

class Tile: public QGraphicsPixmapItem
{

public:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void checkState();
    void capture();
    QString Terrain;
    Tile(QString terrain);




private:
    QString owner;
    int northAttackSide;
    int southAttackSide;
    int westAttackSide;
    int eastAttackSide;

};

#endif // TILE_H
