#include <DecisionMaker.hpp>

#include <Actions.hpp>
#include <PendingDecisions.hpp>

std::unique_ptr<DecisionAnswer> EmptyDecisionMaker::makeDecision(
    const GameState& game_state,
    const PendingDecision& pending_decision)
{
    return nullptr;
}

std::unique_ptr<DecisionAnswer> BuyCardDecisionMaker::makeDecision(
    const GameState& game_state,
    const PendingDecision& pending_decision)
{
    if (dynamic_cast<const ChooseAction*>(&pending_decision) != nullptr)
    {
        return std::make_unique<BuyCard>(m_card_index);
    }

    return nullptr;
}