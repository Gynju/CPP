#ifndef GAME_H
#define GAME_H

#include <QDebug>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QTimer>

#include "Board.h"
#include "Building.h"
#include "Button.h"
#include "Player.h"
#include "Recruiting.h"
#include "Tile.h"
#include "Unit.h"

class Game: public QGraphicsView
{
    Q_OBJECT
public:
    Game();
    void checkWinner();
    void createUnit(int x, int y, QString type, QString terrain, QString owner, int where, int owner_where);
    void drawBorder();
    void drawPanel(int x, int y, int width, int height, QColor color, double opacity, QString text);
    void displayMenu();
    void play(); 
    void showMessage(QString message_text);
    void update();
    void updateText();
    void QMousePressEvent(QGraphicsSceneMouseEvent *event);

    bool building = false;
    bool buttons_exist = false;
    bool cancel_button_exist = false;
    bool recruiting = false;

    int * attacker_actions;
    int attacker_x;
    int attacker_y;
    int click_X;
    int click_Y;
    int message_x;
    int message_y;
    int player_number;
    int possible_actions;
    int resources_income[3];
    int state;

    Button * cancel_button;
    Button * next_turn;
    Button * yes_button;
    Button * no_button;

    QGraphicsTextItem * text[3];
    QGraphicsTextItem * polozenie;
    QGraphicsTextItem * ruch;
    QGraphicsTextItem * message;

    QList<Tile *> tile_list;
    QList<Player *> players_list;

    QString resources_names[3] = {"food", "wood", "stone"};
    QString turn;
    QString what_building;
    QString what_recruit;

    Board * board;
    Player * current_player;
    QGraphicsScene * scene;
    QTimer * timer;

public slots:
    void newTurn();
    void removeMessage();
    void start();
    void quit();

private:
    void drawGUI(int whichPlayer);
};

#endif // GAME_H
