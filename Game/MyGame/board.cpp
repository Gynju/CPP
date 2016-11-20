#include "Board.h"
#include "Game.h"
#include <QDebug>


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
    for(int i=0; i<columns; i++)
    {
        createTileColumn(x+40*i, y, rows, i, columns);
    }
}

void Board::createTileColumn(int x, int y, int numberOfRows, int currentColumn, int numberOfColumns)
{
    if (numberOfColumns%2 == 0)
    {
        if(numberOfRows%2 == 0)
        {
            for(int i=0; i<numberOfRows; i++)
            {
                if((i>((numberOfRows/2)-2)) && (i<((numberOfRows/2)+1)) && (currentColumn>((numberOfColumns/2)-2)) && (currentColumn<((numberOfColumns/2)+1)))
                {
                    Tile * tile = new Tile("fields");
                    tile->setPos(x,y+40*i);
                    tiles.append(tile);
                    game->scene->addItem(tile);
                }
                else
                {
                    Tile * tile = new Tile("water");
                    tile->setPos(x,y+40*i);
                    tiles.append(tile);
                    game->scene->addItem(tile);
                }
            }
        }
        else
        {
            for(int i=0; i<numberOfRows; i++)
            {
                if((i==(numberOfRows/2)) && (currentColumn>((numberOfColumns/2)-2)) && (currentColumn<((numberOfColumns/2)+1)))
                {
                    Tile * tile = new Tile("fields");
                    tile->setPos(x,y+40*i);
                    tiles.append(tile);
                    game->scene->addItem(tile);
                }
                else
                {
                    Tile * tile = new Tile("water");
                    tile->setPos(x,y+40*i);
                    tiles.append(tile);
                    game->scene->addItem(tile);
                }
            }
        }
    }
    else
    {
        if(numberOfRows%2 == 0)
        {
            for(int i=0; i<numberOfRows; i++)
            {
                if((i>((numberOfRows/2)-2)) && (i<((numberOfRows/2)+1)) && (currentColumn==(numberOfColumns/2)) )
                {
                    Tile * tile = new Tile("fields");
                    tile->setPos(x,y+40*i);
                    tiles.append(tile);
                    game->scene->addItem(tile);
                }
                else
                {
                    Tile * tile = new Tile("water");
                    tile->setPos(x,y+40*i);
                    tiles.append(tile);
                    game->scene->addItem(tile);
                }
            }
        }
        else
        {
            for(int i=0; i<numberOfRows; i++)
            {
                if( (i==(numberOfRows/2)) && (currentColumn==(numberOfColumns/2)) )
                {
                    Tile * tile = new Tile("fields");
                    tile->setPos(x,y+40*i);
                    tiles.append(tile);
                    game->scene->addItem(tile);
                }
                else
                {
                    Tile * tile = new Tile("water");
                    tile->setPos(x,y+40*i);
                    tiles.append(tile);
                    game->scene->addItem(tile);
                }
            }
        }
    }
}
