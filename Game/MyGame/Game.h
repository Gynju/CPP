#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <Tile.h>
#include "Board.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget* parent=NULL);
    void displayMenu();
    void play();
    QGraphicsScene * scene;
    Board* board;
    QString Turn;
    //enum States {beginning = 0, idle = 1, player = 2, enemy = 3};
    int state;

    QGraphicsTextItem* polozenie;

public slots:
    void start();
};

#endif // GAME_H
