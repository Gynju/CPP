#include "City.h"
#include "Game.h"

extern Game * game;

City::City()
{
    occupied = false;
    hp = 1;
}

void City::checkHP()
{
    if(hp <= 0)
    {
        if (game->tile_list[list_location]->terrain == "water")
        {
            game->tile_list[list_location]->setPixmap(QPixmap(":img/img/water.png"));
        }
        if(game->tile_list[list_location]->terrain == "fields")
        {
            game->tile_list[list_location]->setPixmap(QPixmap(":img/img/fields.png"));
        }
        if(game->tile_list[list_location]->terrain == "forest")
        {
            game->tile_list[list_location]->setPixmap(QPixmap(":img/img/forest.png"));
        }
        game->tile_list[list_location]->owner = "nobody";
        game->tile_list[list_location]->has_city = false;

        for(int i:subjected_tiles_location)
        {
            game->tile_list[i]->owner = "nobody";
        }
        game->drawBorder();
        game->scene->update();
        for(int i = 0; i < game->players_list.size(); i++)
        {
            if(game->players_list[i]->Name == owner)
            {
                game->players_list.removeAt(i);
            }
        }
        game->checkWinner();
        delete this;
    }
}

void City::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(occupied == true)
    {
        selectUnit();
    }
}

void City::selectUnit()
{
    int index = 0;
    for(int i = 0; i < game->current_player->unit_list.count(); i++)
    {
        if(game->current_player->unit_list[i]->x_position == this->X && game->current_player->unit_list[i]->y_position == this->Y)
        {
            index = i;
            game->current_player->unit_list[index]->selectUnit();
        }
    }
}
