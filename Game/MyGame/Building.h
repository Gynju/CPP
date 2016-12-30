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
    int buildingTime;
    bool built = false;
    bool buttonsExist = false;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    int bonus;

    void updateIcon();
    QString variant;

public slots:
    void build();
    void changeButtonStatus();

private:

    int cost[3] = {0,0,0};

};
#endif // BUILDING_H
