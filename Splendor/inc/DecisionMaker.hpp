#pragma once

#include <memory>

// Forward declerations to avoid circular includes
class GameState;
class PendingDecision;
class DecisionAnswer;

class DecisionMaker
{
public:
    virtual ~DecisionMaker() = default;

    virtual std::unique_ptr<DecisionAnswer> makeDecision(
        const GameState& state,
        const PendingDecision& pending_decision) = 0;
};

class EmptyDecisionMaker : public DecisionMaker
{
    std::unique_ptr<DecisionAnswer> makeDecision(
        const GameState& game_state,
        const PendingDecision& pending_decision) override;
};

class BuyCardDecisionMaker : public DecisionMaker
{
public:
    explicit BuyCardDecisionMaker(int card_index)
        : m_card_index(card_index)
    {
    }

    std::unique_ptr<DecisionAnswer> makeDecision(
        const GameState& game_state,
        const PendingDecision& pending_decision) override;

private:
    int m_card_index;
};