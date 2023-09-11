#include "Game.h"

Game::Game()
{
	this->database = new Database();

}

void Game::init()
{
	this->party = new Party({ 1, 2, 3 }, database);
}
