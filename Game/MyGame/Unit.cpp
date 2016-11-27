#include "Unit.h"
#include "Game.h"
#include "Tile.h"
#include <QDebug>

extern Game * game;
extern Tile * tile;

Unit::Unit(int X, int Y, QString Type, QString terrain)
{

    setPixmap(QPixmap(":img/img/worker.png"));
    x_position = X;
    y_position = Y;
    QRect(x_position, y_position, 40, 40);
    type = Type;
    occupiedTerrain = terrain;
    selected = false;
}

void Unit::move()
{
    QGraphicsTextItem * ruch = new QGraphicsTextItem(QString("Wybierz miejsce na które chcesz przemieścić jendostkę"));
    QFont titleFont("tahoma",24);
    ruch->setFont(titleFont);
    int text_xPosition = game->width()/2 - ruch->boundingRect().width()/2;
    int text_yPosition = 150;
    ruch->setPos(text_xPosition, text_yPosition);
    game->scene->addItem(ruch);
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
    game->scene->addItem(move);
}


void Unit::selectUnit()
{
    this->selected = true;
    this->setPixmap(QPixmap(":img/img/selected_worker.png"));
    showActions();
}

void Unit::selectCity()
{
    for(int i = 0; i < game->tileList.count(); i++)
    {
        if(game->tileList[i]->x_position == this->x_position && game->tileList[i]->y_position == this->y_position)
        {
            game->tileList[i]->checkClicked();
        }
    }
}

void Unit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(occupiedTerrain == "city")
    {
        Button * cit = new Button(QString("Miasto"));
        int cit_xPosition = game->width()/2 - cit->boundingRect().width()/2;
        int cit_yPosition = 275;
        cit->setPos(cit_xPosition, cit_yPosition);
        connect(cit, SIGNAL(clicked()), this, SLOT(selectCity()));
        //connect(cit, SIGNAL(clicked()), this, SLOT());
        game->scene->addItem(cit);

        Button * un = new Button(QString("Jednostka"));
        int un_xPosition = game->width()/2 - un->boundingRect().width()/2;
        int un_yPosition = 350;
        un->setPos(un_xPosition, un_yPosition);
        connect(un, SIGNAL(clicked()), this, SLOT(selectUnit()));
        //connect(un, SIGNAL(clicked()), this, SLOT());
        game->scene->addItem(un);
    }
    else
    {

    }

}


