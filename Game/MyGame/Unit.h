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
    Unit(int X, int Y, QString Type, QString terrain, QString owner, int where, int owner_where);
    void checkHP();
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void showActions();

    int attack_limit;
    int hp;
    int list_location;
    int move_limit;
    int owner_list_location;
    int position;
    int range;
    int x_position;
    int y_position;

    bool attacked;
    bool attack_exist;
    bool greyed_move_exist;
    bool greyed_attack_exist;
    bool move_exist;
    bool moving;
    bool selected;

    Button * attack_button;
    Button * move_button;
    Button * greyed_move;
    Button * greyed_attack;


    QString occupied_terrain;
    QString Owner;

public slots:
    void attack();
    void deselection();
    void move();
    void selectUnit();

private:

    QString type;
};

#endif // UNIT_H
