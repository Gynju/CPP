#include "Tile.h"
#include "Game.h"
#include <QPainter>
#include <QDebug>

extern Game * game;
extern Unit * unit;

Tile::Tile(QString Terrain, int X, int Y)
{
    terrain = Terrain;
    if (terrain == "water")
    {
        setPixmap(QPixmap(":img/img/water.png"));
    }
    if(terrain == "fields")
    {
        setPixmap(QPixmap(":img/img/fields.png"));
    }
    if(terrain == "forest")
    {
        setPixmap(QPixmap(":img/img/forest.png"));
    }
    owner = "nobody";

    x_position = X;
    y_position = Y;
    occupied = false;
    hasCity = false;
    borderExists = false;

    border = new QGraphicsRectItem(x_position, y_position, 40, 40);
    border->setPen(QPen(Qt::red));
}

void Tile::buttonsDelete()
{
    delete yes_button;
    delete no_button;
}

void Tile::selectUnit()
{
    for(int i = 0; i < game->currentPlayer->unitList.count(); i++)
    {
        if(game->currentPlayer->unitList[i]->x_position == this->x_position && game->currentPlayer->unitList[i]->y_position == this->y_position)
        {
            game->currentPlayer->unitList[i]->selectUnit();
        }
    }
}

void Tile::buildOnTerrain()
{
    /*if(game->possibleActions > 0)
    {
        owner = "player";
        terrain = "city";
        setPixmap(QPixmap(":img/img/town.png"));
        game->possibleActions--;

    }
    else
    {
        qDebug()<<"Nie masz więcej akcji";
        capture();
    }*/
    buttonsDelete();
}

void Tile::setBorder()
{
    QString owner = game->currentPlayer->Name;
    int i = this->listLocation;

    game->tileList[i+1]->owner = owner;
    game->tileList[i-1]->owner = owner;
    game->tileList[i]->city->subjectedTilesLocation.append(game->tileList[i+1]->listLocation);
    game->tileList[i]->city->subjectedTilesLocation.append(game->tileList[i-1]->listLocation);
    game->tileList[i+1]->borderExists = true;
    game->tileList[i-1]->borderExists = true;

    game->tileList[i+game->board->height]->owner = owner;
    game->tileList[i-game->board->height]->owner = owner;
    game->tileList[i]->city->subjectedTilesLocation.append(game->tileList[i+game->board->height]->listLocation);
    game->tileList[i]->city->subjectedTilesLocation.append(game->tileList[i-game->board->height]->listLocation);
    game->tileList[i+game->board->height]->borderExists = true;
    game->tileList[i-game->board->height]->borderExists = true;

    game->tileList[(i+game->board->height)-1]->owner = owner;
    game->tileList[(i-game->board->height)-1]->owner = owner;
    game->tileList[i]->city->subjectedTilesLocation.append(game->tileList[(i+game->board->height)-1]->listLocation);
    game->tileList[i]->city->subjectedTilesLocation.append(game->tileList[(i-game->board->height)-1]->listLocation);
    game->tileList[(i+game->board->height)-1]->borderExists = true;
    game->tileList[(i-game->board->height)-1]->borderExists = true;

    game->tileList[(i+game->board->height)+1]->owner = owner;
    game->tileList[(i-game->board->height)+1]->owner = owner;
    game->tileList[i]->city->subjectedTilesLocation.append(game->tileList[(i+game->board->height)+1]->listLocation);
    game->tileList[i]->city->subjectedTilesLocation.append(game->tileList[(i-game->board->height)+1]->listLocation);
    game->tileList[(i+game->board->height)+1]->borderExists = true;
    game->tileList[(i-game->board->height)+1]->borderExists = true;

}

void Tile::settingCity()
{
    if(terrain == "water")
    {
        qDebug() << "Nie można postawić miasta na wodzie";
    }
    else
    {
        if(terrain == "fields")
        {
            game->currentPlayer->resourcesIncome[0] = 5;
            game->currentPlayer->resourcesIncome[1] = 1;
            game->currentPlayer->resourcesIncome[2] = 1;
        }
        else if(terrain == "forest")
        {
            game->currentPlayer->resourcesIncome[0] = 1;
            game->currentPlayer->resourcesIncome[1] = 5;
            game->currentPlayer->resourcesIncome[2] = 1;
        }

        //terrain = "city";
        city = new City();
        city->X = this->x_position;
        city->Y = this->y_position;
        city->listLocation = this->listLocation;

        owner = game->currentPlayer->Name;
        city->owner = game->currentPlayer->Name;

        game->currentPlayer->city_X = city->X;
        game->currentPlayer->city_Y = city->Y;
        game->currentPlayer->cityListLocation = city->listLocation;

        borderExists = true;
        setBorder();
        game->drawBorder();
        setPixmap(QPixmap(":img/img/town.png"));
        game->createUnit(city->X, city->Y, "worker", this->terrain, game->currentPlayer->Name, this->listLocation);
        city->occupied = true;
        occupied = true;
        hasCity = true;

    }
}

void Tile::checkClicked()
{

    if (game->state == 0)//state = 0 - rozpoczynanie gry
    {
        int index = 0;
        settingCity();

        if(game->currentPlayer == game->playersList[game->playersList.size()-1])
        {
            game->currentPlayer = game->playersList[0];
            game->scene->removeItem(game->polozenie);
            game->state = 1;
            game->scene->addItem(game->next_Turn);

        }
        else
        {
            index += 1;
            game->currentPlayer = game->playersList[index];
        }
        game->scene->update();
    }
    else if(game->state == 2) //state == 2 - przemieszczanie jednostki
    {
        for(int i = 0; i < game->currentPlayer->unitList.count(); i++)
        {
            if(game->currentPlayer->unitList[i]->moving == true)
            {
                if(((abs(game->currentPlayer->unitList[i]->x_position - this->x_position)/40) <= game->currentPlayer->unitList[i]->range) && ((abs(game->currentPlayer->unitList[i]->y_position - this->y_position)/40) <= game->currentPlayer->unitList[i]->range))
                {
                    if(hasCity == true)
                    {
                        if(city->owner != game->currentPlayer->Name)
                        {
                            city->hp--;
                            city->checkHP();
                        }
                    }
                    else
                    {

                        qDebug()<< "PORUSZONO";
                        game->tileList[game->currentPlayer->unitList[i]->position]->occupied = false;
                        game->currentPlayer->unitList[i]->position = this->listLocation;
                        game->currentPlayer->unitList[i]->setPos(this->x_position, this->y_position);
                        game->currentPlayer->unitList[i]->x_position = this->x_position;
                        game->currentPlayer->unitList[i]->y_position = this->y_position;
                        game->currentPlayer->unitList[i]->occupiedTerrain = this->terrain;
                        occupied = true;
                    }
                    game->currentPlayer->unitList[i]->moving == false;
                    game->currentPlayer->unitList[i]->selected = false;
                    game->currentPlayer->unitList[i]->setPixmap(QPixmap(":img/img/worker.png"));
                    game->scene->removeItem(game->ruch);
                    game->state = 1;
                }
                else
                {
                    qDebug()<< "JEDNOSTKA NIE MA TAKIEGO ZASIĘGU";
                }
            }
        }
    }   
}

void Tile::capture()
{
    if(owner=="nobody")
    {
        setPixmap(QPixmap(":img/img/players_fields.png"));
        qDebug() << "Przejęto teren";
        owner = "player";
    }
    else if(owner=="player")
    {
        qDebug() << "Teren jest już przez Ciebie zajęty";
    }
    else
    {

    }
}


void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    if(occupied == true)
    {
        selectUnit();
    }
    else
    {
        checkClicked();
    }
    qDebug() << owner;
}


