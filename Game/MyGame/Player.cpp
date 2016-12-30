#include "Player.h"
#include "Game.h"

extern Game * game;

Player::Player(QString name, int food, int wood, int stone)
{
    Name = name;

    resources[0] = 20;
    resources[1] = 20;
    resources[2] = 20;

    resourcesIncome[0] = food;
    resourcesIncome[1] = wood;
    resourcesIncome[2] = stone;

    Building * granary = new Building("granary");
    Building * sawmill = new Building("sawmill");
    Building * stonemason = new Building("stonemason");
    Recruiting * worker = new Recruiting("worker");

    buildingList.append(granary);
    buildingList.append(sawmill);
    buildingList.append(stonemason);

    recruitList.append(worker);

    granary->setPos(0, 400);
    sawmill->setPos(0, 500);
    stonemason->setPos(0, 600);
    worker->setPos(0,700);
}

void Player::updateIcons(int listPosition)
{
    int previousPlayer;
    if(listPosition == 0)
    {
        previousPlayer = game->playersList.size() - 1;
    }
    else
    {
        previousPlayer = listPosition - 1;
    }
    for(int i = 0; i < buildingList.size()-1; i++)
    {
        game->scene->removeItem(game->playersList[previousPlayer]->buildingList[i]);
        game->scene->addItem(buildingList[i]);
    }

    for(int j = 0; j < recruitList.size()-1; j++)
    {
        game->scene->removeItem(game->playersList[previousPlayer]->recruitList[j]);
        game->scene->addItem(recruitList[j]);
    }

}

void Player::updateText()
{
    for(int i = 0; i<3; i++)
    {
        delete game->text[i];
        game->text[i] = new QGraphicsTextItem(game->resourcesNames[i] +": " + QString::number(resources[i]));
        game->text[i]->setPos((i+3)*100, 20);
        game->scene->addItem(game->text[i]);
    }
}

void Player::update()
{
    for(int i = 0; i<3; i++)
    {
        resources[i] += resourcesIncome[i];
    }
}
