#ifndef BOARD_H
#define BOARD_H

#include <QList>
#include <vector>
#include "Tile.h"
#include "Unit.h"

class Board
{
public:
    Board(int Width, int Height);
    int width;
    int height;
    std::vector<int> getTileType(int x, int y);
    void placeTiles(int x, int y);
    std::vector<std::vector<int>*> tiles;
    //std::vector<Tile*> tilesColumn;

private:
};

#endif // BOARD_H
