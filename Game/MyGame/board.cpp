#include "Board.h"
#include "Game.h"
#include <QDebug>


extern Game* game;

Board::Board(int Width, int Height)
{
    width = Width;
    height = Height;
}

QList<Tile *> Board::getTiles()
{
    return tiles;
}

void Board::placeTiles(int x, int y)
{
    int world[width][height];
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            world[i][j] = rand()%3;
            qDebug()<<world[i][j];
        }
    }
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            switch(world[i][j])
            {
                case 0:
                {
                    Tile * tile = new Tile("water");
                    tile->setPos(x+40*i,y+40*j);
                    tiles.append(tile);
                    game->scene->addItem(tile);
                    break;
                }
                case 1:
                {
                    Tile * tile = new Tile("fields");
                    tile->setPos(x+40*i,y+40*j);
                    tiles.append(tile);
                    game->scene->addItem(tile);
                    break;
                }
                case 2:
                {
                    Tile * tile = new Tile("forest");
                    tile->setPos(x+40*i,y+40*j);
                    tiles.append(tile);
                    game->scene->addItem(tile);
                    break;
                }
            }
        }
    }
    /*for(int i=0; i<this->width; i++)
    {
        createTileColumn(x+40*i, y, this->height, i, this->width);
    }*/
}

