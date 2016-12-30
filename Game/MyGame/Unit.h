#ifndef UNIT_H
#define UNIT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QObject>

class Unit:public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Unit(int X, int Y, QString Type, QString terrain, QString owner, int where);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void showActions();


    QString occupiedTerrain;
    bool selected;
    int listLocation;
    int x_position;
    int y_position;
    int position;
    int range = 2;
    bool moving;

public slots:
    void selectUnit();
    void move();


private:
    QString type;
    QString Owner;



};

#endif // UNIT_H
