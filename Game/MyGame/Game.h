#ifndef GAME_H
#define GAME_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "Tile.h"
#include "Unit.h"
#include "Board.h"
#include "Button.h"
//#include "Resources.h"
#include "Building.h"
#include "Recruiting.h"
#include "Player.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    void displayMenu();
    void play();
    void createUnit(int x, int y, QString type, QString terrain, QString owner, int where);
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity, QString text);

    int resources[3];
    QString resourcesNames[3] = {"food", "wood", "stone"};
    int resourcesIncome[3];
    QGraphicsTextItem * text[3];

    //QList<Unit *> unitList;
    QList<Tile *> tileList;
    //QList<Building *> buildingList;
    //QList<Recruiting *> recruitList;

    QList<Player *> playersList;

    QGraphicsScene * scene;
    Board* board;
    QString turn;
    Button * next_Turn;
    //enum States {beginning = 0, idle = 1, player = 2, enemy = 3};
    int state;
    int possibleActions;
    QGraphicsTextItem * polozenie;
    QGraphicsTextItem * ruch;
    //Button next_turn;
    bool building = false;
    bool recruiting = false;

    Player* currentPlayer;

    QString whatBuilding;
    QString whatRecruit;

    int click_X;
    int click_Y;

    int playerNumber;



    void updateText();
    void update();
    void QMousePressEvent(QGraphicsSceneMouseEvent *event);

public slots:
    void start();
    void newTurn();

private:
    void drawGUI(int whichPlayer);
};

#endif // GAME_H
