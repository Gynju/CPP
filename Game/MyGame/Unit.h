#ifndef UNIT_H
#define UNIT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

#include "Button.h"

class Unit:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Unit(int X, int Y, QString Type, QString terrain, QString owner, int where);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void showActions();

    int list_location;
    int move_limit;
    int position;
    int range;
    int x_position;
    int y_position;

    bool greyed_exist;
    bool move_exist;
    bool moving;
    bool selected;

    Button * move_button;
    Button * greyed;

    QString occupied_terrain;

public slots:
    void deselection();
    void move();
    void selectUnit();

private:
    QString Owner;
    QString type;
};

#endif // UNIT_H
