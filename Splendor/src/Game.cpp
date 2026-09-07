#include <Game.hpp>

Game::Game()
    : numberOfPlayers(2)
{
}

int Game::getNumberOfPlayers() const
{
    return numberOfPlayers;
}