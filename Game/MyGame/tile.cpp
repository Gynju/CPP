#include "Tile.h"
#include "Game.h"
#include <QDebug>

extern Game * game;

Tile::Tile(QString terrain)
{
    Terrain = terrain;
    if (Terrain == "water")
    {
        setPixmap(QPixmap(":img/img/water.png"));
    }
    if(Terrain == "fields")
    {
        setPixmap(QPixmap(":img/img/fields.png"));
    }
    owner = "nobody";
}

void Tile::checkState()
{
    if (game->state == 0)
    {
        setPixmap(QPixmap(":img/img/town.png"));
        game->state = 2;
        game->scene->removeItem(game->polozenie);
    }
    else
    {
        if(Terrain == "wate")
        {
            qDebug() << "Nie można przejąć terenu morskiego";
        }
        else
        {
            if(owner=="nobody")
            {
                capture();
            }
            else if(owner=="player")
            {
                qDebug() << "Teren jest już przez Ciebie zajęty";
            }
            else
            {

            };
        }
    }
}

void Tile::capture()
{

    setPixmap(QPixmap(":img/img/players_fields.png"));
    qDebug() << "Przejęto teren";
    owner = "player";

}


void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    checkState();
    game->play();
}

