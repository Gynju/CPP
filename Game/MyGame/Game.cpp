#include "Game.h"
#include "Board.h"
#include "Button.h"
#include <QGraphicsRectItem>


Game::Game(QWidget *parent)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1920,1080);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1920,1080);
    setScene(scene);

    polozenie = new QGraphicsTextItem(QString("Wybierz polozenie miasta"));
    QFont titleFont("tahoma",50);
    polozenie->setFont(titleFont);
    int text_xPosition = this->width()/2 - polozenie->boundingRect().width()/2;
    int text_yPosition = 150;
    polozenie->setPos(text_xPosition, text_yPosition);

}

void Game::displayMenu()
{
    QGraphicsTextItem* title = new QGraphicsTextItem(QString("Poor Civilization Clone"));
    QFont titleFont("tahoma",50);
    title->setFont(titleFont);
    int text_xPosition = this->width()/2 - title->boundingRect().width()/2;
    int text_yPosition = 150;
    title->setPos(text_xPosition, text_yPosition);
    scene->addItem(title);

    Button* playButton = new Button(QString("Play"));
    int playButton_xPosition = this->width()/2 - playButton->boundingRect().width()/2;
    int playButton_yPosition = 275;
    playButton->setPos(playButton_xPosition, playButton_yPosition);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    Button* quitButton = new Button(QString("Quit"));
    int quitButton_xPosition = this->width()/2 - quitButton->boundingRect().width()/2;
    int quitButton_yPosition = 350;
    quitButton->setPos(quitButton_xPosition, quitButton_yPosition);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);

}

void Game::start()
{
    scene->clear();
    board = new Board(48,27);
    board->placeTiles(0,0);
    state = 0;
    scene->addItem(this->polozenie);
    play();


}

void Game::play()
{

    switch(state)
    {
        case 0:
        {
            break;
        }

        case 1:
        {
            break;
        }

        case 2:
        {
            break;
        }

        case 3:
        {
            break;
        }
    }
}
