#include "Tile.h"
#include "Game.h"
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
    int index;
    for(int i = 0; i < game->unitList.count(); i++)
    {
        if(game->unitList[i]->x_position == this->x_position && game->unitList[i]->y_position == this->y_position)
            index = i;
    }
    game->unitList[index]->selected = true;
    game->unitList[index]->setPixmap(QPixmap(":img/img/selected_worker.png"));
    game->unitList[index]->showActions();
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

void Tile::checkClicked()
{
    if (game->state == 0)
    {
        if(terrain == "water")
        {
           //game->board->getTileType(x_position, y_position);
           /*if(game->board->getTileType(x_position, y_position-1) == 0)//tiles[x_position][y_position-1].terrain == "water")
            {
                qDebug() << "Nad tobą tez jest woda";
            }
            else
            {
                qDebug() << "Nad tobą jest ląd";
            }*/
            qDebug() << "Nie można postawić miasta na wodzie";
        }
        else
        {
            owner = "player";
            terrain = "city";
            setPixmap(QPixmap(":img/img/town.png"));
            game->scene->removeItem(game->polozenie);
            game->createUnit(this->x_position, this->y_position, "worker", this->terrain);
            occupied = true;
            game->state = 1;
            game->scene->update();
            //game->scene->addItem(game->nextTurn);
        }
    }
    else if(game->state == 2)
    {
        int index = 0;
        for(int i = 0; i < game->unitList.count(); i++)
        {
            if(game->unitList[i]->x_position == this->x_position && game->unitList[i]->y_position == this->y_position)
                index = i;
        }
        game->unitList[index]->setPos(this->x_position, this->y_position);
        game->state = 1;
    }
    else
    {
        if(terrain == "water")
        {
            qDebug() << "Nie można przejąć terenu morskiego";
        }
        else if(terrain == "city")
        {
            game->drawPanel(0, 0, 80, 1080, Qt::darkCyan, 1, "Player's city");
        }
        else
        {
            //Wyświetlenie przycisków zapytania o budowanie
            yes_button = new Button(QString("Tak"));
            int yes_button_xPosition = game->width()/2 - yes_button->boundingRect().width()/2;
            int yes_button_yPosition = 700;
            yes_button->setPos(yes_button_xPosition, yes_button_yPosition);

            no_button = new Button(QString("Nie"));
            int no_button_xPosition = game->width()/2 - no_button->boundingRect().width()/2;
            int no_button_yPosition = 780;
            no_button->setPos(no_button_xPosition, no_button_yPosition);//Dodać funkcję wykonującą akcję w zależności od rodzaju terenu

            connect(yes_button, SIGNAL(clicked()), this, SLOT(buildOnTerrain()));
            game->scene->addItem(yes_button);
            connect(no_button, SIGNAL(clicked()), this, SLOT(buttonsDelete()));
            game->scene->addItem(no_button);
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

    if(occupied)
    {       
        Button* cit = new Button(QString("Miasto"));
        int cit_xPosition = game->width()/2 - cit->boundingRect().width()/2;
        int cit_yPosition = 275;
        cit->setPos(cit_xPosition, cit_yPosition);
        connect(cit, SIGNAL(clicked()), this, SLOT(checkClicked()));
        //connect(cit, SIGNAL(clicked()), this, SLOT());
        game->scene->addItem(cit);

        Button* un = new Button(QString("Jednostka"));
        int un_xPosition = game->width()/2 - un->boundingRect().width()/2;
        int un_yPosition = 350;
        un->setPos(un_xPosition, un_yPosition);
        connect(un, SIGNAL(clicked()), this, SLOT(selectUnit()));
        game->scene->addItem(un);

    }
    else
    {
        checkClicked();
        game->play();
    }

}

