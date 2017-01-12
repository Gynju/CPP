#include "Game.h"
#include "Recruiting.h"

extern Game * game;

Recruiting::Recruiting(QString Variant)
{
    variant = Variant;
    if(variant == "worker")
    {
        setPixmap(QPixmap(":img/img/worker.png"));
        cost[0] = 20;
        cost[1] = 0;
        cost[2] = 0;
        recruit_time = 5;
    }
}

void Recruiting::changeButtonStatus()
{
    game->buttons_exist = false;
}

void Recruiting::mousePressEvent(QGraphicsSceneMouseEvent *)
{
    if(game->buttons_exist == false && game->state == 1)
    {
        if(game->current_player->recruiting == true)
        {
            game->showMessage("Jedna jednostka właśnie się rekrutuje.");
        }
        else
        {
            game->yes_button = new Button("Rekrutuj", "green");
            int yes_button_xPosition = 100;
            int yes_button_yPosition = 700;
            game->yes_button->setPos(yes_button_xPosition, yes_button_yPosition);

            game->no_button = new Button("Anuluj", "green");
            int no_button_xPosition = 100;
            int no_button_yPosition = 780;
            game->no_button->setPos(no_button_xPosition, no_button_yPosition);

            game->scene->addItem(game->yes_button);
            game->scene->addItem(game->no_button);

            connect(game->yes_button, SIGNAL(clicked()), this, SLOT(recruit()));
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

void Recruiting::recruit()
{
    if(cost[0] <= game->current_player->resources[0] && cost[1] <= game->current_player->resources[1] && cost[2] <= game->current_player->resources[2])
    {
        game->current_player->resources[0] -= cost[0];
        game->current_player->resources[1] -= cost[1];
        game->current_player->resources[2] -= cost[2];
        game->what_recruit = variant;
        game->current_player->recruiting = true;
        updateIcon();
        game->current_player->updateText();
    }
    else
    {
        game->showMessage("Nie stać Cię na zrekrutowanie tej jednostki.");
    }
}

void Recruiting::updateIcon()
{
    if(game->recruiting == true)
    {
        setPixmap(QPixmap(":img/img/buildingDone.png"));
    }
    else
    {
        setPixmap(QPixmap(":img/img/worker.png"));
    }
}
