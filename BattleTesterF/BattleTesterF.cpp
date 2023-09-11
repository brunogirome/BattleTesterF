// BattleTesterF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Game.h"

using namespace std;

int main()
{
    Game* game = new Game();

    game->init();
    
    Party* party;
    
    party = game->party;

    party->addToParty(3);

    for (int i = 0; i < party->partyMembers.size(); i++) {
        cout << party->partyMembers[i].Name << endl;
    }

    cout << "Hello World!\n";
}
