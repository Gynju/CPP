#include "Building.h"
#include "Game.h"

extern Game * game;

Building::Building(QString Variant)
{
    variant = Variant;
    if(variant == "stonemason")
    {
        setPixmap(QPixmap(":img/img/stonemason.png"));
        cost[0] = 2;
        cost[1] = 2;
        cost[2] = 2;
        building_time = 5;
        bonus = 10;
    }
    else if(variant == "sawmill")
    {
        setPixmap(QPixmap(":img/img/sawmill.png"));
        cost[0] = 2;
        cost[1] = 2;
        cost[2] = 2;
        building_time = 5;
        bonus = 20;
    }
    else if(variant == "granary")
    {
        setPixmap(QPixmap(":img/img/granary.png"));
        cost[0] = 2;
        cost[1] = 2;
        cost[2] = 2;
        building_time = 5;
        bonus = 30;
    }
}

void Building::build()
{
    if(cost[0] <= game->current_player->resources[0] && cost[1] <= game->current_player->resources[1] && cost[2] <= game->current_player->resources[2])
    {
        game->current_player->resources[0] -= cost[0];
        game->current_player->resources[1] -= cost[1];
        game->current_player->resources[2] -= cost[2];
        game->what_building = variant;
        game->current_player->building = true;
        game->current_player->updateText();
    }
    else
    {
         game->showMessage("Nie stać Cię na zbudowanie tego budynku");
    }
}

void Building::changeButtonStatus()
{
    game->buttons_exist = false;
}

void Building::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    if(game->buttons_exist == false && game->state == 1)
    {
        if(built == true)
        {
             game->showMessage("Ten budynek jest już zbudowany.");
        }
        else
        {
            if(game->current_player->building == true)
            {
                game->showMessage("Jeden budynek już się buduje, poczekaj aż budowa się zakończy.");
            }
            else
            {
                game->yes_button = new Button("Buduj", "green");
                int yes_button_xPosition = 100;
                int yes_button_yPosition = 700;
                game->yes_button->setPos(yes_button_xPosition, yes_button_yPosition);

                game->no_button = new Button("Anuluj", "green");
                int no_button_xPosition = 100;
                int no_button_yPosition = 780;
                game->no_button->setPos(no_button_xPosition, no_button_yPosition);

                game->scene->addItem(game->yes_button);
                game->scene->addItem(game->no_button);

                connect(game->yes_button, SIGNAL(clicked()), this, SLOT(build()));
                connect(game->yes_button, SIGNAL(clicked()), this, SLOT(changeButtonStatus()));
                connect(game->yes_button, SIGNAL(clicked()), game->no_button, SLOT(deletingButton()));
                connect(game->yes_button, SIGNAL(clicked()), game->yes_button, SLOT(deletingButton()));

                connect(game->no_button, SIGNAL(clicked()), this, SLOT(changeButtonStatus()));
                connect(game->no_button, SIGNAL(clicked()), game->yes_button, SLOT(deletingButton()));
                connect(game->no_button, SIGNAL(clicked()), game->no_button, SLOT(deletingButton()));

                game->buttons_exist = true;
            }
        }

    }
}



void Building::updateIcon()
{
    setPixmap(QPixmap(":img/img/buildingDone.png"));
}


