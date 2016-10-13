#include "Board.h"
#include "Game.h"

extern Game* game;

Board::Board()
{

}

QList<Tile *> Board::getTiles()
{
    return tiles;
}

void Board::placeTiles(int x, int y, int columns, int rows)
{
    for(int i=0, n=columns; i<n; i++)
    {
        createTileColumn(x+40*i, y, rows);
    }
}

void Board::createTileColumn(int x, int y, int numberOfRows)
{
    for(int i=0, n=numberOfRows; i<n; i++)
    {
        Tile * tile = new Tile();
        tile->setPos(x,y+40*i);
        tiles.append(tile);
        game->scene->addItem(tile);
    }
}
