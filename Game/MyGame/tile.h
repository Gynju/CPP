#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

#include "Button.h"
#include "City.h"

class Tile: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tile(QString Terrain, int X, int Y);
    void checkTerrain();
    void colorBorder(QString who_own);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setBorder();
    void settingCity();

    int list_location;
    int x_position;
    int y_position;

    bool border_exists;
    bool has_city;
    bool occupied;

    Button * no_button;
    Button * yes_button;

    City * city;

    QGraphicsRectItem * border;

    QString terrain;  
    QString owner;

public slots:
    void buildOnTerrain();
    void buttonsDelete();
    void checkClicked();
    void selectUnit();
};

#endif // TILE_H
