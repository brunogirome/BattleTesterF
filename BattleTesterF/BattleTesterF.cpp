// BattleTesterF.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include "Database.h"

using namespace std;

int main()
{
    Database* GlobalDatabase = new Database();

    GlobalDatabase->listHeroes();

    cout << "Hello World!\n";
}
