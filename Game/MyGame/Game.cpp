#include "Game.h"

#include <QGraphicsRectItem>
#include <QMediaPlayer>
#include <QDebug>


Game::Game()
{    
    playerNumber = 0;



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

    ruch = new QGraphicsTextItem(QString("Wybierz miejsce na które chcesz przemieścić jendostkę"));
    QFont moveFont("tahoma", 24);
    ruch->setFont(moveFont);
    text_xPosition = width()/2 - ruch->boundingRect().width()/2;
    text_yPosition = 150;
    ruch->setPos(text_xPosition, text_yPosition);

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


void Game::QMousePressEvent(QGraphicsSceneMouseEvent *event)
{
    click_X = floor(QCursor::pos().x()/40)*40;
    click_Y = floor(QCursor::pos().y()/40)*40;
    if(state != 2)
    {
        for(int i = 0; i < currentPlayer->unitList.count(); i++)
        {
            currentPlayer->unitList[i]->selected = false;
            currentPlayer->unitList[i]->setPixmap(QPixmap(":img/img/worker.png"));
        }
    }
}

void Game::newTurn()
{
    if(currentPlayer->Name == playersList[playersList.size()-1]->Name)
    {
        scene->update();
        currentPlayer->update();
        currentPlayer = playersList[0];
        playerNumber = 0;
        currentPlayer->updateText();
        currentPlayer->updateIcons(playerNumber);
    }
    else
    {
        scene->update();
        currentPlayer->update();
        playerNumber += 1;
        currentPlayer = playersList[playerNumber];
        currentPlayer->updateText();
        currentPlayer->updateIcons(playerNumber);
    }
    play();
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

void Game::drawGUI(int whichPlayer)
{
    drawPanel(80, 0, 1880, 80, Qt::darkCyan, 1, "Resources:");
    drawPanel(0, 0, 80, 1080, Qt::darkCyan, 1, "Player's " + QString::number(whichPlayer) + " city");
    for(int i = 0; i<3; i++)
    {
        text[i] = new QGraphicsTextItem(resourcesNames[i] +": " + QString::number(currentPlayer->resources[i]));
        text[i]->setPos((i+3)*100, 20);
        scene->addItem(text[i]);
    }

    scene->addItem(currentPlayer->buildingList[0]);
    scene->addItem(currentPlayer->buildingList[1]);
    scene->addItem(currentPlayer->buildingList[2]);
    scene->addItem(currentPlayer->recruitList[0]);

    next_Turn = new Button(QString("Następna tura"));
    int next_Turn_xPosition = 800;
    int next_Turn_yPosition = 800;
    next_Turn->setPos(next_Turn_xPosition, next_Turn_yPosition);
    connect(next_Turn, SIGNAL(clicked()), this, SLOT(newTurn()));
}

void Game::createUnit(int x, int y, QString type, QString terrain, QString owner, int where)
{
    Unit * unit = new Unit(x, y, type, terrain, owner, where);
    currentPlayer->unitList.append(unit);
    unit->listLocation = currentPlayer->unitList.size()-1;
    unit->setPos(x, y);
    scene->addItem(unit);
}

void Game::drawBorder()
{
    for(int i = 0; i < tileList.count(); i++)
    {
        if(tileList[i]->owner != "nobody")
        {
            scene->addItem(tileList[i]->border);
        }
        else
        {
            if(tileList[i]->borderExists == true)
            {
                scene->removeItem(tileList[i]->border);
            }
        }
    }

}

void Game::checkWinner()
{
    if(playersList.size() == 1)
    {
        scene->clear();
        QGraphicsTextItem* winner = new QGraphicsTextItem(QString("Wygrał " + playersList[0]->Name));
        scene->addItem(winner);
    }
}

void Game::start()
{
    scene->clear();
    board = new Board(46,25);
    board->placeTiles(80,80);

    playersList.append(new Player("Player 1", 0, 0, 0));
    playersList.append(new Player("Player 2", 5, 5, 5));

    currentPlayer = playersList[playerNumber];

    state = 0;
    scene->addItem(this->polozenie);
    drawGUI(playerNumber);
    QMediaPlayer * music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/music/music/backgroundMusic.mp3"));
    music->setVolume(100);
    music->play();




    play();
}

void Game::play()
{

    if(currentPlayer->building)
    {
        for(int i = 0; i < currentPlayer->buildingList.count(); i++)
        {
            if(currentPlayer->buildingList[i]->variant == whatBuilding)
            {
                currentPlayer->buildingList[i]->buildingTime--;
                if(currentPlayer->buildingList[i]->buildingTime <= 0)
                {
                    currentPlayer->building = false;
                    currentPlayer->buildingList[i]->built = true;
                    currentPlayer->resourcesIncome[i] += currentPlayer->buildingList[i]->bonus;
                    currentPlayer->buildingList[i]->updateIcon();
                }
            }
        }
    }
    if(currentPlayer->recruiting)
    {
        for(int i = 0; i < currentPlayer->recruitList.count(); i++)
        {

            if(currentPlayer->recruitList[i]->variant == whatRecruit)
            {
                currentPlayer->recruitList[i]->updateIcon();
                currentPlayer->recruitList[i]->recruitTime--;
                if(currentPlayer->recruitList[i]->recruitTime <= 0)
                {
                    currentPlayer->recruitList[i]->recruitTime = 5;
                    currentPlayer->recruiting = false;
                    currentPlayer->recruitList[i]->updateIcon();
                    createUnit(currentPlayer->city_X, currentPlayer->city_Y, "worker", "city", currentPlayer->Name, currentPlayer->cityListLocation);

                }
            }
        }
    }
    else
    {

    }
    /*switch(state)
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
    }*/
}

