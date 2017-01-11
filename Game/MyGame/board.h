#ifndef BOARD_H
#define BOARD_H

#include <QList>

#include "Tile.h"
#include "Unit.h"

class Board
{
public:
    Board(int Width, int Height);
    void placeTiles(int x, int y);

    int width;
    int height;

    std::vector<std::vector<int>*> tiles;
};

#endif // BOARD_H
