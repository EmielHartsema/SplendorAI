#pragma once

#include <Juwel.hpp>
#include <optional>
#include <utility>

constexpr int size_juwelboard = 5; 
constexpr int nr_slots_on_juwelboard = size_juwelboard * size_juwelboard;

class JuwelBoard
{
public:
    JuwelBoard() = default;

    void refill(JuwelCollection& juwel_bag)
    {   
        for (int i = 0; i < data.size(); ++i)
        {
            if (!data[i].has_value())
            {
                data[i] = juwel_bag.take_random();
            }
        }
    }

    const std::optional<Juwel>& view(const int row, const int col) const
    {
        return data[get_juwel_index(row, col)];
    }

    const std::array<std::optional<Juwel>, nr_slots_on_juwelboard>& view() const
    {
        return data;
    }

    std::optional<Juwel> take(const int row, const int col)
    {
        const int juwel_index = get_juwel_index(row, col);

        if (!data[juwel_index].has_value())
        {
            return std::nullopt;
        }

        Juwel juwel = data[juwel_index].value();
        data[juwel_index].reset();

        return juwel;
    }

private:
    std::array<std::optional<Juwel>, nr_slots_on_juwelboard> data;

    // Mapping for a 5x5 board.
    static constexpr int board_mapping[size_juwelboard][size_juwelboard] =
    {
        {20, 21, 22, 23, 24},
        {19,  6,  7,  8,  9},
        {18,  5,  0,  1, 10},
        {17,  4,  3,  2, 11},
        {16, 15, 14, 13, 12}
    };

    const int get_juwel_index(const int row, const int col) const
    {
        return board_mapping[row][col];
    }
};