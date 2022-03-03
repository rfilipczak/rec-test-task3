#ifndef BRUTE_FORCE_STRATEGY_H
#define BRUTE_FORCE_STRATEGY_H


#include <array>
#include <string>

#include "./Strategy.hpp"


/**
 * /brief O(N) I think... so not so brute-forcy after all
 */
class BruteForceStrategy : public Strategy
{
private:
    static std::array<int,2> count_potholes(const std::string& L1, const std::string& L2);
    static int is_pothole(char c);
    static int calc_score_on_switch(char current_segment, int other_lane_current, int this_lane_total, int this_lane_current);
public:
    [[nodiscard]] int solve(const std::string& L1, const std::string& L2) const override;
};

#endif
