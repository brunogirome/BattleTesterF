#include <iostream>

#include "Game.h"
#include "Battle.h"

using namespace std;

int main()
{
    string input;

    Game* game = new Game();

    game->init();
    
    /*game->GameDatabase->listHeroes();
    
    system("pause");

    system("cls");

    game->GameDatabase->listEnemies();

    system("pause");

    system("cls");*/

    Battle* firstBattle = new Battle(game, {1, 1, 1, 1});

    firstBattle->start();

    cout << "Hello World!\n";
}
