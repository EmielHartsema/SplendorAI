#pragma once

#include <vector>
#include <Juwel.hpp>
#include <Effect.hpp>
#include <utility>

class JuwelCard
{
public:
    JuwelCard(
        JuwelCollection cost,
        JuwelCollection bonus,
        std::vector<Effect> effects,
        int crowns,
        int points)
        : m_cost(std::move(cost)),
          m_bonus(std::move(bonus)),
          m_effects(std::move(effects)),
          m_crowns(crowns),
          m_points(points)
    {}

    const JuwelCollection& cost() const
    {
        return m_cost;
    }

    const JuwelCollection& bonus() const
    {
        return m_bonus;
    }

    const std::vector<Effect>& effects() const
    {
        return m_effects;
    }

    int crowns() const
    {
        return m_crowns;
    }

    int points() const
    {
        return m_points;
    }
private:
    JuwelCollection m_cost;
    JuwelCollection m_bonus;
    std::vector<Effect> m_effects;
    int m_crowns;
    int m_points;
};

// Little builder pattern to construct the cards
class JuwelCardBuilder
{
public:
    // Set Cost
    JuwelCardBuilder& Set_Red_Cost(const int nr_red_cost)
    {
        m_red_cost = nr_red_cost;
        return *this;
    }

    JuwelCardBuilder& Set_Green_Cost(const int nr_green_cost)
    {
        m_green_cost = nr_green_cost;
        return *this;
    }

    JuwelCardBuilder& Set_Blue_Cost(const int nr_blue_cost)
    {
        m_blue_cost = nr_blue_cost;
        return *this;
    }

    JuwelCardBuilder& Set_Black_Cost(const int nr_black_cost)
    {
        m_black_cost = nr_black_cost;
        return *this;
    }

    JuwelCardBuilder& Set_White_Cost(const int nr_white_cost)
    {
        m_white_cost = nr_white_cost;
        return *this;
    }

    JuwelCardBuilder& Set_Pearl_Cost(const int nr_pearl_cost)
    {
        m_pearl_cost = nr_pearl_cost;
        return *this;
    }

    // Set Bonus
    JuwelCardBuilder& Set_Red_Bonus(const int nr_red_bonus)
    {
        m_red_bonus = nr_red_bonus;
        return *this;
    }

    JuwelCardBuilder& Set_Green_Bonus(const int nr_green_bonus)
    {
        m_green_bonus = nr_green_bonus;
        return *this;
    }

    JuwelCardBuilder& Set_Blue_Bonus(const int nr_blue_bonus)
    {
        m_blue_bonus = nr_blue_bonus;
        return *this;
    }

    JuwelCardBuilder& Set_Black_Bonus(const int nr_black_bonus)
    {
        m_black_bonus = nr_black_bonus;
        return *this;
    }

    JuwelCardBuilder& Set_White_Bonus(const int nr_white_bonus)
    {
        m_white_bonus = nr_white_bonus;
        return *this;
    }

    // set effects
    JuwelCardBuilder& Set_Effects(std::vector<Effect> effects)
    {
        m_effects = std::move(effects);
        return *this;
    }

    // Set crowns
    JuwelCardBuilder& Set_Crowns(int nr_crowns)
    {
        m_crowns = nr_crowns;
        return *this;
    }

    // set points
    JuwelCardBuilder& Set_Points(int nr_points)
    {
        m_points = nr_points;
        return *this;
    }

    JuwelCard build()
    {   
        JuwelCollection cost(
            m_red_cost,
            m_green_cost,
            m_blue_cost,
            m_black_cost,
            m_white_cost,
            m_pearl_cost,
            0);

        JuwelCollection bonus(
            m_red_bonus,
            m_green_bonus,
            m_blue_bonus,
            m_black_bonus,
            m_white_bonus,
            0,
            0);
        return JuwelCard( std::move(cost),
                          std::move(bonus),
                          std::move(m_effects),
                          m_crowns,
                          m_points);
    }

private:
    int m_red_cost = 0;
    int m_green_cost = 0;
    int m_blue_cost = 0;
    int m_black_cost = 0;
    int m_white_cost = 0;
    int m_pearl_cost = 0;

    int m_red_bonus = 0;
    int m_green_bonus = 0;
    int m_blue_bonus = 0;
    int m_black_bonus = 0;
    int m_white_bonus = 0;

    std::vector<Effect> m_effects;
    int m_crowns = 0;
    int m_points = 0;
};
