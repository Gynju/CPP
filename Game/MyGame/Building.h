#ifndef BUILDING_H
#define BUILDING_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include "Button.h"

class Building: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Building(QString Variant);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void updateIcon();

    int bonus;
    int building_time;

    bool built = false;

    QString variant;

public slots:
    void build();
    void changeButtonStatus();

private:
    int cost[3] = {0,0,0};

};
#endif // BUILDING_H
