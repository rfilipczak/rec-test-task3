#ifndef FAILING_STRATEGY_H
#define FAILING_STATEGY_H

#include "./Strategy.hpp"

class FailingStrategy : public Strategy
{
public:
    [[nodiscard]] int solve(const std::string &L1 [[maybe_unused]], const std::string &L2 [[maybe_unused]]) const override;
};

#endif
