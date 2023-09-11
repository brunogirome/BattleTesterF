#include "Game.h"

Game::Game()
{
	this->GameDatabase = new Database();
	
	//this->GameDatabase->listHeroes();

	//this->GameDatabase->listEnemies();

}

void Game::init()
{
	this->GameParty = new Party({ 1, 2, 3 }, GameDatabase);
}
	
