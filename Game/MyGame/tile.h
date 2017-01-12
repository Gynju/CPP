#ifndef TILE_H
#define TILE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QObject>

#include "Button.h"
#include "City.h"
#include "Unit.h"

class Tile: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Tile(QString Terrain, int X, int Y);
    void checkTerrain();
    void colorBorder(QString who_own);
    void grantResourceIncome();
    void mousePressEvent(QGraphicsSceneMouseEvent *);
    void setBorder();
    void settingCity();

    int index;
    int list_location;
    int x_position;
    int y_position;

    bool border_exists;
    bool continue_loop;
    bool has_city;
    bool occupied;

    Button * no_button;
    Button * yes_button;

    City * city;

    QGraphicsRectItem * border;

    QString terrain;  
    QString owner;

    Unit * occupied_by;

public slots:
    void buildOnTerrain();
    void buttonsDelete();
    void checkClicked();
    void selectUnit();
};

#endif // TILE_H
