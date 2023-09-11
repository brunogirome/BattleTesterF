#include <iostream>

#include "Game.h"

using namespace std;

int main()
{
    Game* game = new Game();

    game->init();
    
    Party* party;
    
    party = game->party;

    for (int i = 0; i < party->partyMembers.size(); i++) {
        cout << party->partyMembers[i].Name << endl;
    }

    cout << "Hello World!\n";
}
