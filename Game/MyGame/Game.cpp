#include "Game.h"

Game::Game()
{
    test = 0;

    player_number = 0;
    message_x = 1420;
    message_y = 25;

    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(1920,1080);

    scene = new QGraphicsScene();
    scene->setSceneRect(0,0,1920,1080);
    setScene(scene);

    polozenie = new QGraphicsTextItem(QString("Wybierz polozenie miasta"));
    QFont titleFont("tahoma",24);
    polozenie->setFont(titleFont);
    int text_xPosition = message_x;
    int text_yPosition = message_y;
    polozenie->setPos(text_xPosition, text_yPosition);

    ruch = new QGraphicsTextItem(QString("Wybierz miejsce na które chcesz przemieścić jendostkę"));
    QFont moveFont("tahoma", 24);
    ruch->setFont(moveFont);
    text_xPosition = width()/2 - ruch->boundingRect().width()/2;
    text_yPosition = 150;
    ruch->setPos(text_xPosition, text_yPosition);
}

void Game::checkWinner()
{
    if(players_list.size() == 1)
    {
        qDebug()<<state;
        next_turn->deletingButton();

        Button* exitButton = new Button("Exit", "green");
        int exitButton_xPosition = this->width()/2 - exitButton->boundingRect().width()/2;
        int exitButton_yPosition = 275;

        QGraphicsTextItem* winner = new QGraphicsTextItem(QString("Wygrał " + players_list[0]->Name));
        QFont titleFont("tahoma",24);
        winner->setFont(titleFont);
        winner->setPos(exitButton_xPosition - 50, exitButton_yPosition - 100);
        scene->addItem(winner);

        exitButton->setPos(exitButton_xPosition, exitButton_yPosition);
        connect(exitButton, SIGNAL(clicked()), this, SLOT(quit()));
        scene->addItem(exitButton);
        state = 4;
    }
}

void Game::createUnit(int x, int y, QString type, QString terrain, QString owner, int where)
{
    Unit * unit = new Unit(x, y, type, terrain, owner, where, current_player->list_location);
    current_player->unit_list.append(unit);
    unit->list_location = current_player->unit_list.size()-1;
    unit->setPos(x, y);
    scene->addItem(unit);
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

    Button* playButton = new Button("Play", "green");
    int playButton_xPosition = this->width()/2 - playButton->boundingRect().width()/2;
    int playButton_yPosition = 275;
    playButton->setPos(playButton_xPosition, playButton_yPosition);
    connect(playButton, SIGNAL(clicked()), this, SLOT(start()));
    scene->addItem(playButton);

    Button* quitButton = new Button("Quit", "green");
    int quitButton_xPosition = this->width()/2 - quitButton->boundingRect().width()/2;
    int quitButton_yPosition = 350;
    quitButton->setPos(quitButton_xPosition, quitButton_yPosition);
    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    scene->addItem(quitButton);
}

void Game::drawBorder()
{
    for(int i = 0; i < tile_list.count(); i++)
    {
        if(tile_list[i]->owner != "nobody")
        {
            scene->addItem(tile_list[i]->border);
        }
        else
        {
            if(tile_list[i]->border_exists == true)
            {
                scene->removeItem(tile_list[i]->border);
            }
        }
    }
}

void Game::drawGUI(int whichPlayer)
{
    drawPanel(80, 0, 1880, 80, Qt::darkCyan, 1, "Resources:");
    drawPanel(0, 0, 80, 1080, Qt::darkCyan, 1, "Player's " + QString::number(whichPlayer) + " city");
    for(int i = 0; i<3; i++)
    {
        text[i] = new QGraphicsTextItem(resources_names[i] +": " + QString::number(current_player->resources[i]));
        text[i]->setPos((i+3)*100, 20);
        scene->addItem(text[i]);
    }

    scene->addItem(current_player->building_list[0]);
    scene->addItem(current_player->building_list[1]);
    scene->addItem(current_player->building_list[2]);
    scene->addItem(current_player->recruit_list[0]);

    next_turn = new Button("Następna tura", "green");
    int next_turn_xPosition = 800;
    int next_turn_yPosition = 800;
    next_turn->setPos(next_turn_xPosition, next_turn_yPosition);
    connect(next_turn, SIGNAL(clicked()), this, SLOT(newTurn()));
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

void Game::newTurn()
{
    qDebug()<<current_player->unit_list.size();
    if(cancel_button_exist == true)
    {
        cancel_button_exist = false;
        cancel_button->deletingButton();
    }
    if(current_player->unit_list.count() > 0)
    {
        for(int i =0; i < current_player->unit_list.count(); i++)
        {
            current_player->unit_list[i]->deselection();
            current_player->unit_list[i]->move_limit = 1;
            current_player->unit_list[i]->attack_limit = 1;
        }
    }

    if(current_player->Name == players_list[players_list.size()-1]->Name)
    {
        scene->update();
        current_player->update();
        current_player = players_list[0];
        player_number = 0;
        current_player->updateText();
        current_player->updateIcons(player_number);
    }
    else
    {
        scene->update();
        current_player->update();
        player_number += 1;
        current_player = players_list[player_number];
        current_player->updateText();
        current_player->updateIcons(player_number);
    }
    play();
}

void Game::play()
{

    if(current_player->building)
    {
        for(int i = 0; i < current_player->building_list.count(); i++)
        {
            if(current_player->building_list[i]->variant == what_building)
            {
                current_player->building_list[i]->building_time--;
                if(current_player->building_list[i]->building_time <= 0)
                {
                    current_player->building = false;
                    current_player->building_list[i]->built = true;
                    current_player->resources_income[i] += current_player->building_list[i]->bonus;
                    current_player->building_list[i]->updateIcon();
                }
            }
        }
    }
    if(current_player->recruiting)
    {
        for(int i = 0; i < current_player->recruit_list.count(); i++)
        {

            if(current_player->recruit_list[i]->variant == what_recruit)
            {
                current_player->recruit_list[i]->updateIcon();
                current_player->recruit_list[i]->recruit_time--;
                if(current_player->recruit_list[i]->recruit_time <= 0)
                {
                    current_player->recruit_list[i]->recruit_time = 5;
                    current_player->recruiting = false;
                    current_player->recruit_list[i]->updateIcon();
                    createUnit(current_player->city_X, current_player->city_Y, "worker", "city", current_player->Name, current_player->city_list_location);
                }
            }
        }
    }
}

void Game::quit()
{
   close();
}

void Game::QMousePressEvent(QGraphicsSceneMouseEvent *)
{
    click_X = floor(QCursor::pos().x()/40)*40;
    click_Y = floor(QCursor::pos().y()/40)*40;
    if(state != 2)
    {
        for(int i = 0; i < current_player->unit_list.count(); i++)
        {
            current_player->unit_list[i]->selected = false;
            current_player->unit_list[i]->setPixmap(QPixmap(":img/img/worker.png"));
        }
    }
}


void Game::removeMessage()
{
    delete timer;
    scene->removeItem(message);
}

void Game::showMessage(QString message_text)
{
    message = new QGraphicsTextItem(message_text);
    message->setPos(message_x, message_y);
    message->setZValue(1);
    scene->addItem(message);

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(removeMessage()));
    timer->start(1500);
}

void Game::start()
{
    scene->clear();
    board = new Board(46,25);
    board->placeTiles(80,80);

    players_list.append(new Player("Player 1", 0, 0, 0));
    players_list[0]->list_location = 0;
    players_list.append(new Player("Player 2", 5, 5, 5));
    players_list[1]->list_location = 1;

    current_player = players_list[player_number];

    state = 0;
    polozenie->setZValue(1);
    scene->addItem(this->polozenie);
    drawGUI(player_number);
    QMediaPlayer * music = new QMediaPlayer;
    music->setMedia(QUrl("qrc:/music/music/backgroundMusic.mp3"));
    music->setVolume(100);
    music->play();

    play();
}
