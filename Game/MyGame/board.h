#ifndef BOARD_H
#define BOARD_H

#include<QList>
#include "tile.h"

class Board
{
public:
    Board();
    QList<Tile*> getTiles();
    void placeTiles(int x, int y, int columns, int rows);

private:
    void createTileColumn(int x, int y, int numberOfRows);
    QList<Tile*> tiles;
};

#endif // BOARD_H
