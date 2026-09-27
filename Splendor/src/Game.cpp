#include <Game.hpp>
//#include <DecisionMaker.hpp>
//#include <Player.hpp>
#include <Actions.hpp>
#include <PendingDecisions.hpp>
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

void Game::playFirstTurn()
{
    std::cout << "\n=== Player 1's turn ===\n";
    playTurn(m_player_1);
}

void Game::playTurn(Player& player)
{
    ChooseAction pending_decision;

    std::cout << "Requesting an action from the player...\n";

    std::unique_ptr<DecisionAnswer> answer =
        askDecision(player, pending_decision);

    if (answer == nullptr)
    {
        std::cout << "The player returned no action.\n";
        handleInvalidAnswer(player);
        return;
    }

    if (!isValidAnswer(player, pending_decision, *answer))
    {
        std::cout << "The player's action is invalid.\n";
        handleInvalidAnswer(player);
        return;
    }

    if (const auto* buy_card = dynamic_cast<const BuyCard*>(answer.get()))
    {
        std::cout << "Player chose BuyCard, card index "
                  << buy_card->card_index() << ".\n";
    }

    executeAnswer(player, *answer);
}

std::unique_ptr<DecisionAnswer> Game::askDecision(
    Player& player,
    const PendingDecision& pending_decision)
{
    GameState state(*this);

    return player.decisionMaker().makeDecision(
        state,
        pending_decision);
}

bool Game::isValidAnswer(
    Player& player,
    const PendingDecision& pending_decision,
    const DecisionAnswer& answer) const
{
    if (dynamic_cast<const ChooseAction*>(&pending_decision) == nullptr)
        return false;

    const auto* buy_card = dynamic_cast<const BuyCard*>(&answer);
    if (buy_card == nullptr)
        return false;

    const int index = buy_card->card_index();
    if (index < 0 || index >= total_cards)
        return false;

    const JuwelCard* card = nullptr;

    if (index < nr_cards_row_1)
        card = m_card_pyramid.row_1().view(index).has_value()
            ? &m_card_pyramid.row_1().view(index).value() : nullptr;
    else if (index < nr_cards_row_1 + nr_cards_row_2)
    {
        const int slot = index - nr_cards_row_1;
        card = m_card_pyramid.row_2().view(slot).has_value()
            ? &m_card_pyramid.row_2().view(slot).value() : nullptr;
    }
    else
    {
        const int slot = index - nr_cards_row_1 - nr_cards_row_2;
        card = m_card_pyramid.row_3().view(slot).has_value()
            ? &m_card_pyramid.row_3().view(slot).value() : nullptr;
    }

    return card != nullptr && player.can_afford(*card);
}

void Game::executeAnswer(Player& player, const DecisionAnswer& answer)
{
    const auto* buy_card = dynamic_cast<const BuyCard*>(&answer);
    if (buy_card == nullptr)
        return;

    const int index = buy_card->card_index();
    std::optional<JuwelCard> card;

    if (index < nr_cards_row_1)
        card = m_card_pyramid.take(CardLevel::Level1, index);
    else if (index < nr_cards_row_1 + nr_cards_row_2)
        card = m_card_pyramid.take(
            CardLevel::Level2, index - nr_cards_row_1);
    else
        card = m_card_pyramid.take(
            CardLevel::Level3, index - nr_cards_row_1 - nr_cards_row_2);

    if (!card.has_value())
    {
        std::cout << "The selected card is no longer available.\n";
        return;
    }

    if (player.purchase_card(*card))
    {
        std::cout << "Card purchased successfully ("
                  << card->points() << " points).\n";
    }
    else
    {
        std::cout << "The player cannot afford the selected card.\n";
    }
}

void Game::handleInvalidAnswer(Player& player)
{
    std::cout << "Player forfeits the turn.\n";
}

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
