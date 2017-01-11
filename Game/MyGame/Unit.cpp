#include "Game.h"
#include "Unit.h"
#include "Tile.h"

extern Game * game;
extern Tile * tile;

Unit::Unit(int X, int Y, QString Type, QString terrain, QString owner, int where)
{
    moving = false;
    range = 2;
    greyed_exist = false;
    move_exist = false;
    move_limit = 1;
    Owner = owner;
    setPixmap(QPixmap(":img/img/worker.png"));
    x_position = X;
    y_position = Y;
    position = where;
    QRect(x_position, y_position, 40, 40);
    type = Type;
    occupied_terrain = terrain;
    selected = false;
}

void Unit::deselection()
{
    selected = false;
    setPixmap(QPixmap(":img/img/worker.png"));
    if(greyed_exist)
    {
        greyed_exist = false;
        greyed->deletingButton();
    }
    if(move_exist)
    {
        move_exist = false;
        move_button->deletingButton();
    }
}

void Unit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(game->current_player->Name == Owner)
    game->current_player->unit_list[list_location]->selectUnit();
}

void Unit::move()
{
    game->current_player->unit_list[list_location]->moving = true;
    game->scene->addItem(game->ruch);
    game->state = 2;
}

void Unit::selectUnit()
{
    game->current_player->unit_list[list_location]->selected = true;
    game->current_player->unit_list[list_location]->setPixmap(QPixmap(":img/img/selected_worker.png"));
    game->current_player->unit_list[list_location]->showActions();
}

void Unit::showActions()
{
    if(move_limit > 0)
    {
        move_exist = true;
        move_button = new Button("Wykonanie ruchu", "green");
        move_button->setPos(100, 100);
        connect(move_button, SIGNAL(clicked()), this, SLOT(move()));
        connect(move_button, SIGNAL(clicked()), this, SLOT(deselection()));
        game->scene->addItem(move_button);
    }
    else
    {
        if(greyed_exist != true)
        {
            greyed_exist = true;
            greyed = new Button("Limit ruchu wyczerpany", "gray");
            greyed->setPos(100, 100);
            game->scene->addItem(greyed);
        }
    }
}


