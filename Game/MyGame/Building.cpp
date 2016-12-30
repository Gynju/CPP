#include "Building.h"
#include "Game.h"
#include <QDebug>

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
        buildingTime = 5;
        bonus = 10;
    }
    else if(variant == "sawmill")
    {
        setPixmap(QPixmap(":img/img/sawmill.png"));
        cost[0] = 2;
        cost[1] = 2;
        cost[2] = 2;
        buildingTime = 5;
        bonus = 20;
    }
    else if(variant == "granary")
    {
        setPixmap(QPixmap(":img/img/granary.png"));
        cost[0] = 2;
        cost[1] = 2;
        cost[2] = 2;
        buildingTime = 5;
        bonus = 30;
    }
}

void Building::changeButtonStatus()
{
    buttonsExist = false;
}

void Building::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(buttonsExist == false)
    {
        Button * yes_button = new Button(QString("Tak"));
        int yes_button_xPosition = 100;
        int yes_button_yPosition = 700;
        yes_button->setPos(yes_button_xPosition, yes_button_yPosition);

        Button * no_button = new Button(QString("Nie"));
        int no_button_xPosition = 100;
        int no_button_yPosition = 780;
        no_button->setPos(no_button_xPosition, no_button_yPosition);

        game->scene->addItem(yes_button);
        game->scene->addItem(no_button);

        connect(yes_button, SIGNAL(clicked()), this, SLOT(build()));
        connect(yes_button, SIGNAL(clicked()), this, SLOT(changeButtonStatus()));
        connect(yes_button, SIGNAL(clicked()), no_button, SLOT(deletingButton()));
        connect(yes_button, SIGNAL(clicked()), yes_button, SLOT(deletingButton()));

        connect(no_button, SIGNAL(clicked()), this, SLOT(changeButtonStatus()));
        connect(no_button, SIGNAL(clicked()), yes_button, SLOT(deletingButton()));
        connect(no_button, SIGNAL(clicked()), no_button, SLOT(deletingButton()));

        buttonsExist = true;
    }

}



void Building::build()
{
    if(cost[0] <= game->resources[0] && cost[1] <= game->resources[1] && cost[2] <= game->resources[2])
    {
        if(built == true)
        {
            qDebug()<< "Ten budynek jest już zbudowany.";
        }
        else
        {
            if(game->building == true)
            {
                qDebug()<< "Jeden budynek już się buduje, poczekaj aż budowa się zakończy.";
            }
            else
            {
                game->currentPlayer->resources[0] -= cost[0];
                game->currentPlayer->resources[1] -= cost[1];
                game->currentPlayer->resources[2] -= cost[2];
                game->whatBuilding = variant;
                game->currentPlayer->building = true;
                game->currentPlayer->updateText();
            }
        }
    }
    else
    {
        qDebug()<<"Nie stać Cię na zbudowanie tego budynku";
    }


}

void Building::updateIcon()
{

    setPixmap(QPixmap(":img/img/buildingDone.png"));

}


