#include "Game.h"
#include <QGraphicsRectItem>


Game::Game()
{
    possibleActions = 2;

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

    /*next_turn = new Button(QString("Koniec tury"));
    int next_turn_xPosition = this->width()/2 - next_turn->boundingRect().width()/2;
    int next_turn_yPosition = 275;
    next_turn->setPos(next_turn_xPosition, next_turn_yPosition);
    connect(next_turn, SIGNAL(clicked()), this, SLOT(nextTurn()));*/

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

void Game::drawPanel(int x, int y, int width, int height, QColor color, double opacity, QString text)
{
   QGraphicsTextItem * name = new QGraphicsTextItem(text);
   QGraphicsRectItem * panel = new QGraphicsRectItem(x, y, width, height);
   QBrush brush;
   brush.setStyle(Qt::SolidPattern);
   brush.setColor(color);
   panel->setBrush(brush);
   panel->setOpacity(opacity);
   scene->addItem(panel);
   name->setPos(x+20, y+20);
   scene->addItem(name);
}

void Game::drawGUI()
{
    //drawPanel(0, 0, 80, 1080, Qt::darkCyan, 1, "City");
    drawPanel(80, 0, 1880, 80, Qt::darkCyan, 1, "Resources:");
    //city->setPos(20,0);



}

void Game::createUnit(int x, int y, QString type, QString terrain)
{
    Unit * unit = new Unit(x, y, type, terrain);
    unitList.append(unit);
    unit->listLocation = unitList.size()-1;
    unit->setPos(x, y);
    scene->addItem(unit);
}


void Game::start()
{
    scene->clear();
    board = new Board(46,25);
    board->placeTiles(80,80);
    state = 0;
    scene->addItem(this->polozenie);
    drawGUI();
    play();


}

void Game::nextTurn()
{

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

