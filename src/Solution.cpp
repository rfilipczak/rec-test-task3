#include "Solution.hpp"

Solution::Solution(std::unique_ptr<Strategy> strategy)
        : strategy_(std::move(strategy))
{
}

[[maybe_unused]] void Solution::set_strategy(std::unique_ptr<Strategy> strategy)
{
    this->strategy_ = std::move(strategy);
}

[[nodiscard]] int Solution::solve(const std::string& L1, const std::string& L2) const
{
    return this->strategy_->solve(L1, L2);
}
