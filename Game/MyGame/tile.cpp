#include <QPainter>

#include "Game.h"
#include "Tile.h"

extern Game * game;
extern Unit * unit;

Tile::Tile(QString Terrain, int X, int Y)
{
    continue_loop = false;
    index = 0;
    terrain = Terrain;
    if (terrain == "water")
    {
        setPixmap(QPixmap(":img/img/water.png"));
    }
    if(terrain == "fields")
    {
        setPixmap(QPixmap(":img/img/fields.png"));
    }
    if(terrain == "forest")
    {
        setPixmap(QPixmap(":img/img/forest.png"));
    }
    owner = "nobody";

    x_position = X;
    y_position = Y;
    occupied = false;
    has_city = false;
    border_exists = false;

    border = new QGraphicsRectItem(x_position, y_position, 40, 40);
    border->setPen(QPen(Qt::black));
}

void Tile::buildOnTerrain()
{
    buttonsDelete();
}

void Tile::buttonsDelete()
{
    delete yes_button;
    delete no_button;
}

void Tile::checkClicked()
{

    if (game->state == 0)//state = 0 - rozpoczynanie gry
    {

        checkTerrain();

        if(game->current_player == game->players_list[game->players_list.size()-1] && continue_loop == true)
        {
            game->current_player = game->players_list[0];
            game->scene->removeItem(game->polozenie);
            game->state = 1;
            game->scene->addItem(game->next_turn);
        }
        else
        {
            if(continue_loop == true)
            {
                index += 1;
                game->current_player = game->players_list[index];
            }
        }
        game->scene->update();
    }
    else if(game->state == 1)
    {
        for(int i = 0; i < game->current_player->unit_list.count(); i++)
        {
            if(game->current_player->unit_list[i]->selected == true)
            {
                game->current_player->unit_list[i]->deselection();
            }
        }
    }
    else if(game->state == 2) //state == 2 - przemieszczanie jednostki
    {
        for(int i = 0; i < game->current_player->unit_list.count(); i++)
        {
            if(game->current_player->unit_list[i]->moving == true)
            {
                if(((abs(game->current_player->unit_list[i]->x_position - this->x_position)/40) <= game->current_player->unit_list[i]->range) && ((abs(game->current_player->unit_list[i]->y_position - this->y_position)/40) <= game->current_player->unit_list[i]->range))
                {
                    if(terrain != "water")
                    {
                        game->state = 1;
                        if(has_city == true)
                        {
                            if(city->owner != game->current_player->Name)
                            {
                                city->hp--;
                                city->checkHP();
                            }
                        }
                        game->showMessage("Przemieszczono jednostkę");
                        game->current_player->unit_list[i]->move_limit -= 1;
                        game->tile_list[game->current_player->unit_list[i]->position]->occupied = false;
                        game->current_player->unit_list[i]->position = this->list_location;
                        game->current_player->unit_list[i]->setPos(this->x_position, this->y_position);
                        game->current_player->unit_list[i]->x_position = this->x_position;
                        game->current_player->unit_list[i]->y_position = this->y_position;
                        game->current_player->unit_list[i]->occupied_terrain = this->terrain;
                        occupied = true;
                        occupied_by = game->current_player->unit_list[i];
                        game->current_player->unit_list[i]->moving = false;
                        game->current_player->unit_list[i]->deselection();
                        game->scene->removeItem(game->ruch);
                    }
                    else
                    {
                        game->showMessage("Nie można przemieścić jednostki na wodę.");
                    }
                }
                else
                {
                    game->showMessage("JEDNOSTKA NIE MA TAKIEGO ZASIĘGU");
                }
            }
        }
    }
}

void Tile::checkTerrain()
{
    if(terrain == "water")
    {
        game->showMessage("Nie można postawić miasta na wodzie.");
        continue_loop = false;
    }
    else if(game->current_player->list_location > 0 && (((abs(this->x_position - game->players_list[game->current_player->list_location-1]->city_X))/40 < 3) && ((abs(this->y_position - game->players_list[game->current_player->list_location-1]->city_Y))/40 < 3)))
    {
        game->showMessage("Nie można postawić miasta zbyt blisko miasta przeciwnika.");
        continue_loop = false;
    }
    else
    {
        settingCity();
        continue_loop = true;
    }
}

void Tile::colorBorder(QString who_own)
{
    if(who_own == "Player 1")
    {
        border->setPen(QPen(Qt::red));
    }
    else
    {
        border->setPen(QPen(Qt::yellow));
    }
}

void Tile::grantResourceIncome()
{
    if(terrain == "fields")
    {
        game->current_player->resources_income[0] = 5;
        game->current_player->resources_income[1] = 1;
        game->current_player->resources_income[2] = 1;
    }
    else if(terrain == "forest")
    {
        game->current_player->resources_income[0] = 1;
        game->current_player->resources_income[1] = 5;
        game->current_player->resources_income[2] = 1;
    }
}

void Tile::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(occupied == true)
    {
        selectUnit();
    }
    else
    {
        checkClicked();
    }
}

void Tile::selectUnit()
{
    for(int i = 0; i < game->current_player->unit_list.count(); i++)
    {
        if(game->current_player->unit_list[i]->x_position == this->x_position && game->current_player->unit_list[i]->y_position == this->y_position)
        {
            game->current_player->unit_list[i]->selectUnit();
        }
    }
}

void Tile::setBorder()
{
    QString owner = game->current_player->Name;
    int i = this->list_location;

    game->tile_list[i+1]->owner = owner;
    game->tile_list[i-1]->owner = owner;
    game->tile_list[i]->city->subjected_tiles_location.append(game->tile_list[i+1]->list_location);
    game->tile_list[i]->city->subjected_tiles_location.append(game->tile_list[i-1]->list_location);
    game->tile_list[i+1]->border_exists = true;
    game->tile_list[i-1]->border_exists = true;
    game->tile_list[i+1]->colorBorder(owner);
    game->tile_list[i-1]->colorBorder(owner);

    game->tile_list[i+game->board->height]->owner = owner;
    game->tile_list[i-game->board->height]->owner = owner;
    game->tile_list[i]->city->subjected_tiles_location.append(game->tile_list[i+game->board->height]->list_location);
    game->tile_list[i]->city->subjected_tiles_location.append(game->tile_list[i-game->board->height]->list_location);
    game->tile_list[i+game->board->height]->border_exists = true;
    game->tile_list[i-game->board->height]->border_exists = true;
    game->tile_list[i+game->board->height]->colorBorder(owner);
    game->tile_list[i-game->board->height]->colorBorder(owner);

    game->tile_list[(i+game->board->height)-1]->owner = owner;
    game->tile_list[(i-game->board->height)-1]->owner = owner;
    game->tile_list[i]->city->subjected_tiles_location.append(game->tile_list[(i+game->board->height)-1]->list_location);
    game->tile_list[i]->city->subjected_tiles_location.append(game->tile_list[(i-game->board->height)-1]->list_location);
    game->tile_list[(i+game->board->height)-1]->border_exists = true;
    game->tile_list[(i-game->board->height)-1]->border_exists = true;
    game->tile_list[(i+game->board->height)-1]->colorBorder(owner);
    game->tile_list[(i-game->board->height)-1]->colorBorder(owner);

    game->tile_list[(i+game->board->height)+1]->owner = owner;
    game->tile_list[(i-game->board->height)+1]->owner = owner;
    game->tile_list[i]->city->subjected_tiles_location.append(game->tile_list[(i+game->board->height)+1]->list_location);
    game->tile_list[i]->city->subjected_tiles_location.append(game->tile_list[(i-game->board->height)+1]->list_location);
    game->tile_list[(i+game->board->height)+1]->border_exists = true;
    game->tile_list[(i-game->board->height)+1]->border_exists = true;
    game->tile_list[(i+game->board->height)+1]->colorBorder(owner);
    game->tile_list[(i-game->board->height)+1]->colorBorder(owner);
}

void Tile::settingCity()
{
    grantResourceIncome();
    city = new City();
    city->X = this->x_position;
    city->Y = this->y_position;
    city->list_location = this->list_location;

    owner = game->current_player->Name;
    city->owner = owner;

    game->current_player->city_X = city->X;
    game->current_player->city_Y = city->Y;
    game->current_player->city_list_location = city->list_location;

    colorBorder(owner);
    border_exists = true;
    setBorder();
    game->drawBorder();
    setPixmap(QPixmap(":img/img/town.png"));
    game->createUnit(city->X, city->Y, "worker", this->terrain, owner, this->list_location, game->current_player->list_location);
    city->occupied = true;
    occupied = true;
    has_city = true;
}



