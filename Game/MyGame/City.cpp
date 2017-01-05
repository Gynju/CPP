#include "City.h"
#include "game.h"

#include <QDebug>

extern Game * game;

City::City()
{
    occupied = false;
    hp = 1;
}

void City::selectUnit()
{
    int index = 0;
    for(int i = 0; i < game->currentPlayer->unitList.count(); i++)
    {
        if(game->currentPlayer->unitList[i]->x_position == this->X && game->currentPlayer->unitList[i]->y_position == this->Y)
        {
            index = i;
            game->currentPlayer->unitList[index]->selectUnit();
        }
    }
}

void City::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(occupied == true)
    {
        selectUnit();
    }
    else
    {
        //checkClicked();
    }
}

void City::checkHP()
{
    if(hp <= 0)
    {
        if (game->tileList[listLocation]->terrain == "water")
        {
            game->tileList[listLocation]->setPixmap(QPixmap(":img/img/water.png"));
        }
        if(game->tileList[listLocation]->terrain == "fields")
        {
            game->tileList[listLocation]->setPixmap(QPixmap(":img/img/fields.png"));
        }
        if(game->tileList[listLocation]->terrain == "forest")
        {
            game->tileList[listLocation]->setPixmap(QPixmap(":img/img/forest.png"));
        }
        game->tileList[listLocation]->owner = "nobody";
        game->tileList[listLocation]->hasCity = false;

        for(int i:subjectedTilesLocation)
        {
            game->tileList[i]->owner = "nobody";
        }
        game->drawBorder();
        game->scene->update();
        for(int i = 0; i < game->playersList.size(); i++)
        {
            if(game->playersList[i]->Name == owner)
            {
                game->playersList.removeAt(i);
                qDebug()<<"Raz dwa trzy miasto zniszczone";
                qDebug()<< game->playersList.size();
            }
        }
        delete this;
        game->checkWinner();
    }
}
