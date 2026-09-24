#pragma once

#include <VictoryCondition.hpp>
//#include <Player.hpp>
//#include <DecisionMaker.hpp>
//#include <Action.hpp>
#include <JuwelCardPyramid.hpp>
#include <Juwel.hpp>
#include <JuwelBoard.hpp>
//#include <CrownCard.hpp>
//#include <CardRow.hpp>

// The game object stores the state of the shared game board.
// Any modifications to the shared game board must be made using the public interface.
// Here the rules of the game will be enforced.
// Also player interactions (such as stealing from your opponent) will pass trough the game board such that rules can be enforced.
class Game
{
public:
    // Constructor
    Game(std::unique_ptr<DecisionMaker> decision_maker_1,
         std::unique_ptr<DecisionMaker> decision_maker_2);

    //void PerformAction(Action action);

    //bool ValidateAction(Action action); 
    
    const VictoryCondition& victory_condition() const
    {
        return m_victory_condition;
    }

    int nr_privilege_scrolls() const
    {
        return m_nr_privilege_scrolls;
    }

    const JuwelCardPyramid& card_pyramid() const
    {
        return m_card_pyramid;
    }

    const JuwelBoard& juwel_board() const
    {
        return m_juwel_board;
    }
    
private:
    Player m_player_1;
    Player m_player_2;
    
    // Components of the shared game board
    VictoryCondition m_victory_condition;
    int m_nr_privilege_scrolls;
    JuwelCardPyramid m_card_pyramid;
    JuwelCollection m_juwel_bag;
    JuwelBoard m_juwel_board;
    //CardRow<CrownCard, 4> crowncards;

    // Get the JuwelCards level 1 from the box
    std::vector<JuwelCard> get_juwel_cards1();
    std::vector<JuwelCard> get_juwel_cards2();
    std::vector<JuwelCard> get_juwel_cards3();
};