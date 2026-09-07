#include <iostream>

#include <Game.hpp>

int main()
{
    Game game;

    std::cout << "Splendor started!" << '\n';
    std::cout << "Players: "
              << game.getNumberOfPlayers()
              << '\n';

    return 0;
}