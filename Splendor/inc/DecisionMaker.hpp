#pragma once

#include <Action.hpp>
//#include <GameState.hpp>

class DecisionMaker
{
public:
    virtual ~DecisionMaker() = default;
    //Action ChooseAction(GameState state);
};

class EmptyDecisionMaker : public DecisionMaker
{

};