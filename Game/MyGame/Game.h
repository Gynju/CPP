#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include "Tile.h"
#include "Unit.h"
#include "Board.h"
#include "Button.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    void displayMenu();
    void play();
    void createUnit(int x, int y, QString type, QString terrain);
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity, QString text);

    QList<Unit *> unitList;
    QList<Tile *> tileList;
    QGraphicsScene * scene;
    Board* board;
    QString Turn;
    //enum States {beginning = 0, idle = 1, player = 2, enemy = 3};
    int state;
    int possibleActions;
    QGraphicsTextItem * polozenie;
    //Button next_turn;

public slots:
    void start();
    void nextTurn();

private:
    void drawGUI();
};

#endif // GAME_H
