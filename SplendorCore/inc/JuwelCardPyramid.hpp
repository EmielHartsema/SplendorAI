#pragma once

#include <utility>
#include <vector>
#include <CardRow.hpp>
#include <JuwelCard.hpp>

constexpr int nr_card_rows = 3;
constexpr int nr_cards_row_1 = 5;
constexpr int nr_cards_row_2 = 4;
constexpr int nr_cards_row_3 = 3;
constexpr int total_cards = nr_cards_row_1 + nr_cards_row_2 + nr_cards_row_3;

enum class CardLevel
{
    Level1,
    Level2,
    Level3
};

class JuwelCardPyramid
{
public:

    JuwelCardPyramid(
        std::vector<JuwelCard> card_set_1,
        std::vector<JuwelCard> card_set_2,
        std::vector<JuwelCard> card_set_3)
        : card_row_1(std::move(card_set_1)),
          card_row_2(std::move(card_set_2)),
          card_row_3(std::move(card_set_3))
    {
    }

    const CardRow<JuwelCard, nr_cards_row_1>& row_1() const
    {
        return card_row_1;
    }

    const CardRow<JuwelCard, nr_cards_row_2>& row_2() const
    {
        return card_row_2;
    }

    const CardRow<JuwelCard, nr_cards_row_3>& row_3() const
    {
        return card_row_3;
    }

    std::optional<JuwelCard> take(CardLevel row, int slot)
{
    switch (row)
    {
    case CardLevel::Level1:
        return card_row_1.take(slot);

    case CardLevel::Level2:
        return card_row_2.take(slot);

    case CardLevel::Level3:
        return card_row_3.take(slot);
    }

    return std::nullopt;
}

private:
    CardRow<JuwelCard, nr_cards_row_1> card_row_1;
    CardRow<JuwelCard, nr_cards_row_2> card_row_2;
    CardRow<JuwelCard, nr_cards_row_3> card_row_3;

};