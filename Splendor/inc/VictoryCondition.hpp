#pragma once

#include <Player.hpp>

class VictoryCondition
{
public:
    VictoryCondition( int nr_points_to_win,
                      int nr_points_single_catagory_to_win,
                      int nr_crowns_to_win)
                      : m_nr_points_to_win                    ( nr_points_to_win),
                        m_nr_points_single_catagory_to_win    ( nr_points_single_catagory_to_win),
                        m_nr_crowns_to_win                    ( nr_crowns_to_win)
                      
    {
    };

    bool CheckVictory(const Player& player) const;

    // Define const getters
    int view_nr_points_to_win() const
    {
        return m_nr_points_to_win;
    }
    int view_nr_points_single_catagory_to_win() const
    {
        return m_nr_points_single_catagory_to_win;
    }
    int view_nr_crowns_to_win() const
    {
        return m_nr_crowns_to_win;
    }

private:
    const int m_nr_points_to_win;
    const int m_nr_points_single_catagory_to_win;
    const int m_nr_crowns_to_win;
};