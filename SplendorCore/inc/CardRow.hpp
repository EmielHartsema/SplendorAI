#pragma once

#include <array>
#include <vector>
#include <optional>
#include <iterator>
#include <random>
#include <algorithm>
#include <iostream>

template< class T, std::size_t nr_open_cards >
class CardRow
{
public:
    CardRow(std::vector<T> card_set)
        : closed_stack(std::move(card_set))
    {    
        // shuffle
        std::random_device rd;
        std::mt19937 gen(rd());
        std::shuffle(closed_stack.begin(), closed_stack.end(), gen);

        // reveal the top cards
        for (int i = 0; i < nr_open_cards && !closed_stack.empty(); ++i)
        {
            open_cards[i].emplace(std::move(closed_stack.back()));
            closed_stack.pop_back();
        };
    };

    const std::optional<T>& view(const int slot) const
    {
        return open_cards[slot];
    }

    const std::array<std::optional<T>, nr_open_cards>& view() const
    {
        return open_cards;
    }

    std::optional<T> take(const int slot)
    {
        if (!open_cards[slot].has_value())
            return std::nullopt;

        std::optional<T> result = std::move(open_cards[slot]);
        open_cards[slot].reset();

        refill(slot);

        return result;
    }

private:

    void refill(const int slot)
    {
        if (closed_stack.empty())
            return;

        open_cards[slot].emplace(std::move(closed_stack.back()));
        closed_stack.pop_back();
    }
    std::vector<T> closed_stack;
    std::array<std::optional<T>, nr_open_cards> open_cards;
};