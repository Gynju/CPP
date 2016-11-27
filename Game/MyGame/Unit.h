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
    Unit(int X, int Y, QString Type, QString terrain);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void showActions();


    QString occupiedTerrain;
    bool selected;
    int listLocation;
    int x_position;
    int y_position;

public slots:
    void selectUnit();
    void selectCity();
    void move();


private:
    QString type;



};

#endif // UNIT_H
