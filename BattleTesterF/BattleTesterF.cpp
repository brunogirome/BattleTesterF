#include <iostream>

#include "Game.h"
#include "Battle.h"

int main()
{
    Game* game = new Game();

    game->init();
    
    bool debug = false;
    if (debug) {
        game->GameDatabase->listHeroes();

        system("pause");

        system("cls");

        game->GameDatabase->listEnemies();

        system("pause");

        system("cls");
    }

    Battle* firstBattle = new Battle(game, {3, 3});

    firstBattle->start();

    std::cout << "Hello World!\n";
}
