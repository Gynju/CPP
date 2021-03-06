#include "Board.h"
#include "Game.h"

extern Game* game;

Board::Board(int Width, int Height)
{
    width = Width;
    height = Height;
}

void Board::placeTiles(int x, int y)
{
    int world[width][height];
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            world[i][j] = rand()%3;
        }
    }
    for(int i = 0; i < width; i++)
    {
        std::vector<int> * tilesColumn = new std::vector<int>;
        for(int j = 0; j < height; j++)
        {
            switch(world[i][j])
            {
                case 0:
                {
                    Tile * tile = new Tile("water", x+40*i, y+40*j);
                    game->tile_list.append(tile);
                    tile->list_location = game->tile_list.size()-1;
                    tile->setPos(x+40*i,y+40*j);
                    tilesColumn->push_back(0);
                    game->scene->addItem(tile);
                    break;
                }
                case 1:
                {
                    Tile * tile = new Tile("fields", x+40*i, y+40*j);
                    game->tile_list.append(tile);
                    tile->list_location = game->tile_list.size()-1;
                    tile->setPos(x+40*i,y+40*j);
                    tilesColumn->push_back(1);
                    game->scene->addItem(tile);
                    break;
                }
                case 2:
                {
                    Tile * tile = new Tile("forest", x+40*i, y+40*j);
                    game->tile_list.append(tile);
                    tile->list_location = game->tile_list.size()-1;
                    tile->setPos(x+40*i, y+40*j);
                    tilesColumn->push_back(2);
                    game->scene->addItem(tile);
                    break;
                }
            }
        }
        tiles.push_back(tilesColumn);
    }
}

