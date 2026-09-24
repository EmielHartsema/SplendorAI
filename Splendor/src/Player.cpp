#include <Player.hpp>

Player::Player(std::unique_ptr<DecisionMaker> decision_maker)
    : m_nr_privilege_scrolls(0),
      m_decision_maker(std::move(decision_maker))
{
}