#include "Game.h"
#include "Unit.h"
#include "Tile.h"

extern Game * game;
extern Tile * tile;

Unit::Unit(int X, int Y, QString Type, QString terrain, QString owner, int where, int owner_where)
{
    owner_list_location = owner_where;
    attack_limit = 1;
    attacked = false;
    hp = 1;
    moving = false;
    range = 2;
    greyed_move_exist = false;
    greyed_attack_exist = false;
    move_exist = false;
    move_limit = 1;
    Owner = owner;
    setPixmap(QPixmap(":img/img/worker.png"));
    x_position = X;
    y_position = Y;
    position = where;
    list_location = game->current_player->unit_list.size();
    QRect(x_position, y_position, 40, 40);
    type = Type;
    occupied_terrain = terrain;
    selected = false;
}

void Unit::attack()
{
    game->state = 3;

    game->attacker_x = this->x_position;
    game->attacker_y = this->y_position;
    game->attacker_actions = &attack_limit;

    game->cancel_button_exist = true;
    game->cancel_button = new Button("Anuluj", "green");
    game->cancel_button->setPos(100, 100);
    connect(game->cancel_button, SIGNAL(clicked()), this, SLOT(selectUnit()));
    connect(game->cancel_button, SIGNAL(clicked()), game->cancel_button, SLOT(deletingButton()));
    game->scene->addItem(game->cancel_button);
}

void Unit::checkHP()
{
    if(hp <= 0)
    {
        game->tile_list[position]->occupied = false;
        game->players_list[owner_list_location]->unit_list.removeAt(list_location);
        delete this;
    }
}

void Unit::deselection()
{
    selected = false;
    setPixmap(QPixmap(":img/img/worker.png"));
    if(greyed_move_exist)
    {
        greyed_move_exist = false;
        greyed_move->deletingButton();
    }
    if(greyed_attack_exist)
    {
        greyed_attack_exist = false;
        greyed_attack->deletingButton();
    }
    if(move_exist)
    {
        move_exist = false;
        move_button->deletingButton();
    }
    if(attack_exist)
    {
        attack_exist = false;
        attack_button->deletingButton();
    }
}

void Unit::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(game->current_player->Name == Owner)
    {
        game->current_player->unit_list[list_location]->selectUnit();
    }
    else if(game->state == 3 && game->current_player->Name != Owner)
    {
        game->showMessage("Zaatakowano wrogą jednostkę.");
        if(abs(x_position - game->attacker_x)/40 <= 1 && abs(y_position - game->attacker_y)/40 <= 1)
        {
            *game->attacker_actions = 0;
            game->cancel_button_exist = false;
            game->cancel_button->deletingButton();
            game->state = 1;
            hp--;
            checkHP();
        }
    }
}

void Unit::move()
{
    game->current_player->unit_list[list_location]->moving = true;
    game->scene->addItem(game->ruch);
    game->state = 2;
}

void Unit::selectUnit()
{
    if(game->cancel_button_exist == true)
    {
        game->cancel_button_exist = false;
        game->cancel_button->deletingButton();
    }
    game->current_player->unit_list[list_location]->selected = true;
    game->current_player->unit_list[list_location]->setPixmap(QPixmap(":img/img/selected_worker.png"));
    game->current_player->unit_list[list_location]->showActions();
}

void Unit::showActions()
{
    qDebug()<<*game->attacker_actions;
    qDebug()<<attack_limit;
    qDebug()<<"======";
    game->state = 1;
    if(move_limit > 0)
    {
        move_exist = true;
        move_button = new Button("Wykonanie ruchu", "green");
        move_button->setPos(100, 100);
        connect(move_button, SIGNAL(clicked()), this, SLOT(move()));    
        connect(move_button, SIGNAL(clicked()), this, SLOT(deselection()));
        game->scene->addItem(move_button);
    }
    else if(greyed_move_exist != true)
    {
        greyed_move_exist = true;
        greyed_move = new Button("Limit ruchu wyczerpany", "gray");
        greyed_move->setPos(100, 100);
        game->scene->addItem(greyed_move);
    }

    if(attack_limit > 0)
    {
        attack_exist = true;
        attack_button = new Button("Atak", "green");
        attack_button->setPos(100, 150);
        connect(attack_button, SIGNAL(clicked()), this, SLOT(attack()));
        connect(attack_button, SIGNAL(clicked()), this, SLOT(deselection()));

        game->scene->addItem(attack_button);
    }
    else if(greyed_attack_exist != true)
    {
        greyed_attack_exist = true;
        greyed_attack = new Button("Limit ataku wyczerpany", "gray");
        greyed_attack->setPos(100, 150);
        game->scene->addItem(greyed_attack);
    }

}
