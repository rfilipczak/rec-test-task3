#ifndef STRATEGY_H
#define STRATEGY_H

#include <string>

class Strategy
{
public:
    [[nodiscard]] virtual int solve(const std::string& L1, const std::string& L2) const = 0;

    virtual ~Strategy() = default;
};

#endif
