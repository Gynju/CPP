#include "Recruiting.h"
#include "Game.h"
#include <QDebug>

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
        recruitTime = 5;
    }
}

void Recruiting::changeButtonStatus()
{
    buttonsExist = false;
}

void Recruiting::mousePressEvent(QGraphicsSceneMouseEvent *event)
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

        connect(yes_button, SIGNAL(clicked()), this, SLOT(recruit()));
        connect(yes_button, SIGNAL(clicked()), this, SLOT(changeButtonStatus()));
        connect(yes_button, SIGNAL(clicked()), no_button, SLOT(deletingButton()));
        connect(yes_button, SIGNAL(clicked()), yes_button, SLOT(deletingButton()));

        connect(no_button, SIGNAL(clicked()), this, SLOT(changeButtonStatus()));
        connect(no_button, SIGNAL(clicked()), yes_button, SLOT(deletingButton()));
        connect(no_button, SIGNAL(clicked()), no_button, SLOT(deletingButton()));

        buttonsExist = true;
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

void Recruiting::recruit()
{
    if(cost[0] <= game->currentPlayer->resources[0] && cost[1] <= game->currentPlayer->resources[1] && cost[2] <= game->currentPlayer->resources[2])
    {

        if(game->recruiting == true)
        {
            qDebug()<< "Jedna jednostka właśnie się rekrutuje.";
        }
        else
        {
            game->currentPlayer->resources[0] -= cost[0];
            game->currentPlayer->resources[1] -= cost[1];
            game->currentPlayer->resources[2] -= cost[2];
            game->whatRecruit = variant;
            game->currentPlayer->recruiting = true;
            updateIcon();
            game->currentPlayer->updateText();
        }
    }
    else
    {
        qDebug()<<"Nie stać Cię na zrekrutowanie tej jednostki";
    }


}
