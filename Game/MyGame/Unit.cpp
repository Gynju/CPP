#include "Unit.h"
#include "Game.h"
#include "Tile.h"
#include <QDebug>

extern Game * game;
extern Tile * tile;

Unit::Unit(int X, int Y, QString Type, QString terrain, QString owner, int where)
{

    Owner = owner;
    setPixmap(QPixmap(":img/img/worker.png"));
    x_position = X;
    y_position = Y;
    position = where;
    QRect(x_position, y_position, 40, 40);
    type = Type;
    occupiedTerrain = terrain;
    selected = false;
}

void Unit::move()
{
    this->moving = true;
    game->scene->addItem(game->ruch);
    game->state = 2;
    qDebug() << "wololo";
}


void Unit::showActions()
{
    Button * move = new Button(QString("Wykonanie ruchu"));
    int move_xPosition = 100;
    int move_yPosition = 100;
    move->setPos(move_xPosition, move_yPosition);
    connect(move, SIGNAL(clicked()), this, SLOT(move()));
    connect(move, SIGNAL(clicked()), move, SLOT(deletingButton()));
    game->scene->addItem(move);
}


void Unit::selectUnit()
{
    this->selected = true;
    this->setPixmap(QPixmap(":img/img/selected_worker.png"));
    this->showActions();
}

void Unit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    /*
    if(occupiedTerrain == "city")
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

        connect(cit, SIGNAL(clicked()), this, SLOT(selectCity()));
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
    if(game->currentPlayer->Name == Owner)
    this->selectUnit();

}


