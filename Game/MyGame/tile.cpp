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
}

void Tile::buttonsDelete()
{
    delete yes_button;
    delete no_button;
}

void Tile::selectUnit()
{
    int index = 0;
    for(int i = 0; i < game->currentPlayer->unitList.count(); i++)
    {
        if(game->currentPlayer->unitList[i]->x_position == this->x_position && game->currentPlayer->unitList[i]->y_position == this->y_position)
        {
            index = i;
            qDebug()<< "LOL";
            game->currentPlayer->unitList[index]->selectUnit();
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

void Tile::drawBorder()
{
    for(int i = 0; i < game->tileList.count(); i++)
    {
        if(game->tileList[i]->owner != "nobody")
        {
            QGraphicsRectItem * rec = new QGraphicsRectItem(game->tileList[i]->x_position, game->tileList[i]->y_position, 40, 40);
            rec->setPen(QPen(Qt::red));
            game->scene->addItem(rec);
        }
    }

}

void Tile::setBorder()
{
    QString owner = game->currentPlayer->Name;
    int i = this->listLocation;
    game->tileList[i+1]->owner = owner;
    game->tileList[i-1]->owner = owner;

    game->tileList[i+game->board->height]->owner = owner;
    game->tileList[i-game->board->height]->owner = owner;

    game->tileList[(i+game->board->height)-1]->owner = owner;
    game->tileList[(i-game->board->height)-1]->owner = owner;

    game->tileList[(i+game->board->height)+1]->owner = owner;
    game->tileList[(i-game->board->height)+1]->owner = owner;
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
        owner = game->currentPlayer->Name;
        terrain = "city";
        game->currentPlayer->city_X = this->x_position;
        game->currentPlayer->city_Y = this->y_position;
        game->currentPlayer->cityListLocation = this->listLocation;
        setBorder();
        drawBorder();
        setPixmap(QPixmap(":img/img/town.png"));
        game->createUnit(this->x_position, this->y_position, "worker", this->terrain, game->currentPlayer->Name, this->listLocation);
        occupied = true;
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
                    game->currentPlayer->unitList[i]->moving == false;
                    qDebug()<< "PORUSZONO";
                    game->tileList[game->currentPlayer->unitList[i]->position]->occupied = false;
                    game->currentPlayer->unitList[i]->position = this->listLocation;
                    game->currentPlayer->unitList[i]->setPos(this->x_position, this->y_position);
                    game->currentPlayer->unitList[i]->x_position = this->x_position;
                    game->currentPlayer->unitList[i]->y_position = this->y_position;
                    game->currentPlayer->unitList[i]->selected = false;
                    game->currentPlayer->unitList[i]->setPixmap(QPixmap(":img/img/worker.png"));
                    game->currentPlayer->unitList[i]->occupiedTerrain = this->terrain;
                    game->scene->removeItem(game->ruch);
                    game->state = 1;
                    occupied = true;
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
        /*
        if(terrain == "city")
        {
            Button * cit = new Button(QString("Miasto"));
            int cit_xPosition = game->width()/2 - cit->boundingRect().width()/2;
            int cit_yPosition = 275;
            cit->setPos(cit_xPosition, cit_yPosition);
            game->scene->addItem(cit);

            Button * un = new Button(QString("Jednostka"));
            int un_xPosition = game->width()/2 - un->boundingRect().width()/2;
            int un_yPosition = 350;
            un->setPos(un_xPosition, un_yPosition);
            game->scene->addItem(un);

            connect(cit, SIGNAL(clicked()), this, SLOT(checkClicked()));
            connect(cit, SIGNAL(clicked()), un, SLOT(deletingButton()));
            connect(cit, SIGNAL(clicked()), cit, SLOT(deletingButton()));


            connect(un, SIGNAL(clicked()), this, SLOT(selectUnit()));
            connect(un, SIGNAL(clicked()), cit, SLOT(deletingButton()));
            connect(un, SIGNAL(clicked()), un, SLOT(deletingButton()));
        }
        else
        {
            selectUnit();
        }
        */
        selectUnit();
    }
    else
    {
        checkClicked();
    }
    qDebug() << occupied;
}


