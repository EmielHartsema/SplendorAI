#include <iostream>

#include <GameState.hpp>
#include <Game.hpp>
#include <DecisionMaker.hpp>


int main()
{
    auto decision_maker_1 = std::make_unique<EmptyDecisionMaker>();
    auto decision_maker_2 = std::make_unique<EmptyDecisionMaker>();

    Game game( std::move(decision_maker_1),
               std::move(decision_maker_2));

    GameState state(game);
    state.print();

    return 0;
}