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

    QGraphicsScene * scene;
    Board* board;
    QString Turn;

public slots:
    void start();
};

#endif // GAME_H
