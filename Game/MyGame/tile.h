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

    //void mousePressEvent(QGraphicsSceneMouseEvent *event);

    void capture();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setBorder();
    void settingCity();

    QString terrain;  
    QString owner;
    Button * yes_button;
    Button * no_button;

    QGraphicsRectItem * border;

    bool occupied;
    bool hasCity;
    bool borderExists;
    int listLocation;
    int x_position;
    int y_position;

    City* city;


public slots:
    void buildOnTerrain();
    void buttonsDelete();
    void selectUnit();
    void checkClicked();


};

#endif // TILE_H
