#pragma once

#include <iostream>
#include <optional>
#include <JuwelCardPyramid.hpp>
#include <JuwelBoard.hpp>



// class PlayerState
// {
// public:
//     // Information from privilege scrolls in game holding
//     const int nr_privilege_scrolls;

//     // Information from Juwel Card pyramid
//     const std::vector<std::optional<JuwelCard>> juwel_cards;

//     // information from JuwelCollection
//     JuwelCollection juwel_inventory;
// };

class Game;

class GameState
{
public:
    GameState( const Game& game);

    void print();

private:

    // Information from Victory Condition
    int nr_points_to_win;
    int nr_points_single_catagory_to_win;
    int nr_crowns_to_win;

    // Information from privilege scrolls in game holding
    int nr_privilege_scrolls;

    // Information from Juwel Card pyramid
    std::array<std::optional<JuwelCard>, nr_cards_row_1> juwel_cards_1;
    std::array<std::optional<JuwelCard>, nr_cards_row_2> juwel_cards_2;
    std::array<std::optional<JuwelCard>, nr_cards_row_3> juwel_cards_3;

    // information from JuwelBoard
    std::array<std::optional<Juwel>, nr_slots_on_juwelboard> juwel_board;

    // //information from player 1
    // PlayerState player_1;

    // //information from player 1
    // PlayerState player_2;

    void print_juwel_collection(const JuwelCollection& collection);

    template <std::size_t N>
    void print_card_row(const std::array<std::optional<JuwelCard>, N>& row)
    {
        for (const auto& card_opt : row)
        {
            if (card_opt.has_value())
            {
                const JuwelCard& card = card_opt.value();

                print_juwel_collection(card.bonus());
                std::cout << card.crowns() << " Crown(s), ";
                std::cout << card.points() << " Point(s)\n";
            }
            else
            {
                std::cout << "[empty slot]\n";
            }
        }
    };
};

