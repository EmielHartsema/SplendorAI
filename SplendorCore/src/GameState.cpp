#include <GameState.hpp>
#include <Game.hpp>


GameState::GameState( const Game& game)
    : nr_points_to_win                 (game.victory_condition().view_nr_points_to_win()),
      nr_points_single_catagory_to_win (game.victory_condition().view_nr_points_single_catagory_to_win()),
      nr_crowns_to_win                 (game.victory_condition().view_nr_crowns_to_win()),
      nr_privilege_scrolls             (game.nr_privilege_scrolls()),
      juwel_cards_1                    (game.card_pyramid().row_1().view()),
      juwel_cards_2                    (game.card_pyramid().row_2().view()),
      juwel_cards_3                    (game.card_pyramid().row_3().view()),
      juwel_board                      (game.juwel_board().view())
{ }


void GameState::print_juwel_collection(const JuwelCollection& collection)
{
    if (collection.amount(Juwel::Red) > 0)
    {
        std::cout << collection.amount(Juwel::Red) << " Red, ";
    }
    if (collection.amount(Juwel::Green) > 0)
    {
        std::cout << collection.amount(Juwel::Green) << " Green, ";
    }  
    if (collection.amount(Juwel::Blue) > 0)
    {
        std::cout << collection.amount(Juwel::Blue) << " Blue, ";
    }  
    if (collection.amount(Juwel::Black) > 0)
    {
        std::cout << collection.amount(Juwel::Black) << " Black, ";
    }  
    if (collection.amount(Juwel::White) > 0)
    {
        std::cout << collection.amount(Juwel::White) << " White, ";
    }  
    if (collection.amount(Juwel::Pearl) > 0)
    {
        std::cout << collection.amount(Juwel::Pearl) << " Pearl, ";
    }  
    if (collection.amount(Juwel::Gold) > 0)
    {
        std::cout << collection.amount(Juwel::Gold) << " Gold, ";
    }  
}

void GameState::print()
{
    // printing victory condition
    std::cout << "Victory condition: \n";
    std::cout << "Number of points needed to win: " << nr_points_to_win << "\n";
    std::cout << "Number of points in a Juwel catagory needed to win: " << nr_points_single_catagory_to_win << "\n";
    std::cout << "Number of crowns needed to win: " << nr_crowns_to_win << "\n";
    std::cout << "\n";

    std::cout << "number of available privilege scrolls: " <<  nr_privilege_scrolls << "\n";
    std::cout <<  "\n";

    std::cout << "Information from Juwel Card pyramid" << "\n";
    print_card_row(juwel_cards_1);
    print_card_row(juwel_cards_2);
    print_card_row(juwel_cards_3);
    std::cout <<  "\n";
    
    std::cout << "Information from Juwel Board" << "\n";
    for (const std::optional<Juwel>& juwel : juwel_board)
    {
        if (juwel.has_value())
        {
            switch (juwel.value())
            {
            case Juwel::Red:
                std::cout << "Red " ;
                break;
            case Juwel::Green:
                std::cout << "Green " ;
                break;
            case Juwel::Blue:
                std::cout << "Blue " ;
                break;
            case Juwel::Black:
                std::cout << "Black " ;
                break;
            case Juwel::White:
                std::cout << "White " ;
                break;
            case Juwel::Pearl:
                std::cout << "Pearl " ;
                break;
            case Juwel::Gold:
                std::cout << "Gold " ;
                break;
            }
        }
    }

    std::cout << std::endl;
};

