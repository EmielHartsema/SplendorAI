#pragma once

#include <vector>
#include <memory>
#include <JuwelCard.hpp>
#include <DecisionMaker.hpp>

//#include <Action.hpp>
//#include <GameState.hpp>

class Player
{
public:
    explicit Player(std::unique_ptr<DecisionMaker> decision_maker);

    //Action get_action(const GameState& state);
    //std::vector<Action> actions;

private:
    // private components of the player
    JuwelCollection m_juwels;
    std::vector<JuwelCard> m_juwelcards_owned;
    int m_nr_privilege_scrolls;

    std::unique_ptr<DecisionMaker> m_decision_maker;
};