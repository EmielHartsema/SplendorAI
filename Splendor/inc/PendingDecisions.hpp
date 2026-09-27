#pragma once

#include <memory>
#include <vector>

#include <Actions.hpp>

class PendingDecision
{
public:
    virtual ~PendingDecision() = default;
};

class ChooseAction : public PendingDecision
{
};

class ChooseCrownCard : public PendingDecision
{
};

class ChooseWildcardJuwel : public PendingDecision
{
};

class ChooseJuwelToSteal : public PendingDecision
{
};

class ChooseJuwelFromBoard : public PendingDecision
{
};