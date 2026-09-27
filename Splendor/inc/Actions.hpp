#pragma once

class DecisionAnswer
{
public:
    virtual ~DecisionAnswer() = default;
};

class Action : public DecisionAnswer
{
public:
    virtual ~Action() = default;
};


class MandatoryAction : public Action
{
public:
    virtual ~MandatoryAction() = default;
};


class OptionalAction : public Action
{
public:
    virtual ~OptionalAction() = default;
};

class TakeJuwels : public MandatoryAction
{
public:
    // TODO: specify which jewels are being taken
};

class BuyCard : public MandatoryAction
{
public:
    explicit BuyCard(int card_index)
        : m_card_index(card_index)
    {
    }

    int card_index() const
    {
        return m_card_index;
    }

private:
    int m_card_index;
};

class ReserveCard : public MandatoryAction
{
};

class RefillBoard : public OptionalAction
{
};

class UsePrivilege : public OptionalAction
{
public:
    // TODO: specify what jewel is being taken
};