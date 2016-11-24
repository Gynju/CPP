#ifndef BOARD_H
#define BOARD_H

#include<QList>
#include "tile.h"

class Board
{
public:
    Board(int Width, int Height);
    int width;
    int height;
    QList<Tile*> getTiles();
    void placeTiles(int x, int y);

private:
    QList<Tile*> tiles;
};

#endif // BOARD_H
