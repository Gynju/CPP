#include "Game.h"
#include "Player.h"

extern Game * game;

Player::Player(QString name, int food, int wood, int stone)
{
    Name = name;

    resources[0] = 20;
    resources[1] = 20;
    resources[2] = 20;

    resources_income[0] = food;
    resources_income[1] = wood;
    resources_income[2] = stone;

    Building * granary = new Building("granary");
    Building * sawmill = new Building("sawmill");
    Building * stonemason = new Building("stonemason");
    Recruiting * worker = new Recruiting("worker");

    building_list.append(granary);
    building_list.append(sawmill);
    building_list.append(stonemason);

    recruit_list.append(worker);

    granary->setPos(0, 400);
    sawmill->setPos(0, 500);
    stonemason->setPos(0, 600);
    worker->setPos(0,700);
}

void Player::update()
{
    for(int i = 0; i<3; i++)
    {
        resources[i] += resources_income[i];
    }
}

void Player::updateIcons(int list_position)
{
    int previousPlayer;
    if(list_position == 0)
    {
        previousPlayer = game->players_list.size() - 1;
    }
    else
    {
        previousPlayer = list_position - 1;
    }
    for(int i = 0; i < building_list.size()-1; i++)
    {
        game->scene->removeItem(game->players_list[previousPlayer]->building_list[i]);
        game->scene->addItem(building_list[i]);
    }

    for(int j = 0; j < recruit_list.size()-1; j++)
    {
        game->scene->removeItem(game->players_list[previousPlayer]->recruit_list[j]);
        game->scene->addItem(recruit_list[j]);
    }
}

void Player::updateText()
{
    for(int i = 0; i<3; i++)
    {
        delete game->text[i];
        game->text[i] = new QGraphicsTextItem(game->resources_names[i] +": " + QString::number(resources[i]));
        game->text[i]->setPos((i+3)*100, 20);
        game->scene->addItem(game->text[i]);
    }
}
