#include <Game.hpp>
//#include <DecisionMaker.hpp>
//#include <Player.hpp>
#include <iostream>

constexpr int max_nr_red_juwels   = 4;
constexpr int max_nr_green_juwels = 4;
constexpr int max_nr_blue_juwels  = 4;
constexpr int max_nr_black_juwels = 4;
constexpr int max_nr_white_juwels = 4;
constexpr int max_nr_pearl_juwels = 2;
constexpr int max_nr_gold_juwels  = 3;

constexpr int nr_points_to_win    = 20;
constexpr int nr_points_single_catagory_to_win = 10;
constexpr int nr_crowns_to_win = 10;

Game::Game(std::unique_ptr<DecisionMaker> decision_maker_1,
           std::unique_ptr<DecisionMaker> decision_maker_2)
    : m_player_1(std::move(decision_maker_1)),
      m_player_2(std::move(decision_maker_2)),
      m_victory_condition( nr_points_to_win,
                           nr_points_single_catagory_to_win,
                           nr_crowns_to_win),
      m_nr_privilege_scrolls(3),
      m_card_pyramid( get_juwel_cards1(),
                      get_juwel_cards2(),
                      get_juwel_cards3()),
      m_juwel_bag( max_nr_red_juwels, 
                   max_nr_green_juwels,
                   max_nr_blue_juwels,
                   max_nr_black_juwels,
                   max_nr_white_juwels,
                   max_nr_pearl_juwels,
                   max_nr_gold_juwels)
{
    m_juwel_board.refill(m_juwel_bag);
};


// void Game::SubmitAction(Action action);
// {
//     if (ValidateAction(action))
//     {
//         PerformAction(action);
//     }
// };

// void Game::PerformAction(Action action)
// {
    

// };


// bool Game::ValidateAction(Action action)
// {
//     return true;
// };

std::vector<JuwelCard> Game::get_juwel_cards1()
{
    std::vector<JuwelCard> juwel_cards = {};

    //placeholders
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(2).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(3).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(4).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(5).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(6).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(7).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(8).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(9).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(10).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(0).build());

    return juwel_cards;
}

std::vector<JuwelCard> Game::get_juwel_cards2()
{
    std::vector<JuwelCard> juwel_cards = {};

    //placeholders
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).Set_Black_Cost(2).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());

    return juwel_cards;
}

std::vector<JuwelCard> Game::get_juwel_cards3()
{
    std::vector<JuwelCard> juwel_cards = {};

    //placeholders
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());
    juwel_cards.push_back(JuwelCardBuilder().Set_Points(1).build());

    return juwel_cards;
}
