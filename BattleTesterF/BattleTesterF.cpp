#include <iostream>

#include "Game.h"
#include "Battle.h"

int main()
{
    std::string input;

    Game* game = new Game();

    game->init();
    
    bool debug = true;
    if (debug) {
        game->GameDatabase->listHeroes();

        system("pause");

        system("cls");

        game->GameDatabase->listEnemies();

        system("pause");

        system("cls");
    }

    Battle* firstBattle = new Battle(game, {1, 1, 2, 2});

    firstBattle->start();

    std::cout << "Hello World!\n";
}
