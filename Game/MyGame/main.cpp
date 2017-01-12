#include <ctime>
#include <QApplication>
#include <QDebug>

#include "Game.h"

Game * game;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    QApplication a(argc, argv);

    game = new Game();
    game->show();
    game->displayMenu();

    return a.exec();
}
