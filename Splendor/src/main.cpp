#include <iostream>

#include <GameState.hpp>
#include <Game.hpp>
#include <DecisionMaker.hpp>


int main()
{
    auto decision_maker_1 = std::make_unique<BuyCardDecisionMaker>(0);
    auto decision_maker_2 = std::make_unique<EmptyDecisionMaker>();

    Game game( std::move(decision_maker_1),
               std::move(decision_maker_2));

    std::cout << "Initial game state:\n";
    GameState initial_state(game);
    initial_state.print();

    game.playFirstTurn();

    std::cout << "\nGame state after Player 1's turn:\n";
    GameState updated_state(game);
    updated_state.print();

    return 0;
}