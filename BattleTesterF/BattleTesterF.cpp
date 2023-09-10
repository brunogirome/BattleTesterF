// BattleTesterF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Database.h"

using namespace std;

int main()
{
    Database* GlobalDatabase = new Database();

    GlobalDatabase->listHeroes();

    const Hero hero1 = GlobalDatabase->getAHero(0);

    cout << hero1.Name << endl;

    cout << "Hello World!\n";
}
