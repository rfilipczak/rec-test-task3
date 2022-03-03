#ifndef SOLUTION_H
#define SOLUTION_H

#include "./Strategy.hpp"

#include <memory>

class Solution
{
private:
    std::unique_ptr<Strategy> strategy_;
public:
    explicit Solution(std::unique_ptr<Strategy> strategy);

    [[maybe_unused]] void set_strategy(std::unique_ptr<Strategy> strategy);

    [[nodiscard]] int solve(const std::string& L1, const std::string& L2) const;
};

#endif
