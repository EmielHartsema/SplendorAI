#include <Player.hpp>

#include <algorithm>
#include <array>
namespace
{
    constexpr std::array colors{
        Juwel::Red, Juwel::Green, Juwel::Blue,
        Juwel::Black, Juwel::White, Juwel::Pearl
    };

    JuwelCollection owned_bonuses(const std::vector<JuwelCard>& cards)
    {
        JuwelCollection bonuses;

        for (const JuwelCard& card : cards)
        {
            for (Juwel color : colors)
            {
                for (int count = 0; count < card.bonus().amount(color); ++count)
                    bonuses.add(color);
            }
        }

        return bonuses;
    }

    bool pay_cost(
        JuwelCollection& inventory,
        const JuwelCard& card,
        const JuwelCollection& discounts)
    {
        std::array<int, colors.size()> payments{};
        int gold_needed = 0;

        for (std::size_t i = 0; i < colors.size(); ++i)
        {
            const Juwel color = colors[i];
            const int required = std::max(
                0, card.cost().amount(color) - discounts.amount(color));

            payments[i] = std::min(required, inventory.amount(color));
            gold_needed += required - payments[i];
        }

        if (gold_needed > inventory.amount(Juwel::Gold))
            return false;

        for (std::size_t i = 0; i < colors.size(); ++i)
        {
            for (int count = 0; count < payments[i]; ++count)
                inventory.remove(colors[i]);
        }

        for (int count = 0; count < gold_needed; ++count)
            inventory.remove(Juwel::Gold);

        return true;
    }
}

Player::Player(std::unique_ptr<DecisionMaker> decision_maker)
    : m_nr_privilege_scrolls(0),
      m_decision_maker(std::move(decision_maker))
{
}

bool Player::can_afford(const JuwelCard& card) const
{
    JuwelCollection remaining = m_juwels;
    const JuwelCollection discounts = owned_bonuses(m_juwelcards_owned);
    return pay_cost(remaining, card, discounts);
}

bool Player::purchase_card(const JuwelCard& card)
{
    const JuwelCollection discounts = owned_bonuses(m_juwelcards_owned);

    if (!pay_cost(m_juwels, card, discounts))
        return false;

    m_juwelcards_owned.push_back(card);
    return true;
}