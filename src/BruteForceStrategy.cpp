#include <algorithm>

#include "../include/BruteForceStrategy.hpp"


std::array<int,2> BruteForceStrategy::count_potholes(const std::string& L1, const std::string& L2)
{
    auto L1_count = 0;
    auto L2_count = 0;

    for (size_t i = 0; i < L1.length(); ++i)
    {
        L1_count += is_pothole(L1.at(i));
        L2_count += is_pothole(L2.at(i));
    }

    return {L1_count, L2_count};
}

int BruteForceStrategy::is_pothole(char c)
{
    return c == 'x';
}

int BruteForceStrategy::calc_score_on_switch(char current_segment, int other_lane_current, int this_lane_total, int this_lane_current)
{
    return this_lane_total - this_lane_current + other_lane_current - is_pothole(current_segment);
}

[[nodiscard]] int BruteForceStrategy::solve(const std::string& L1, const std::string& L2) const
{
    // general gist of the algorithm is to decide on which segment should the change of lanes happen (if at all)

    auto [L1_total_pothole_count, L2_total_pothole_count] = count_potholes(L1, L2);

    int best = std::max(L1_total_pothole_count, L2_total_pothole_count);

    if (std::min(L1_total_pothole_count, L2_total_pothole_count) == 0)
        return best; // possible early return when one of the lines have no potholes

    int L1_current_potholes_count = 0;
    int L2_current_potholes_count = 0;

    for (size_t i = 1; i < L1.length() - 1; ++i)
    {
        // we count the potholes up to the current segment (excluding)
        L1_current_potholes_count += is_pothole(L1[i - 1]);
        L2_current_potholes_count += is_pothole(L2[i - 1]);

        // now we calculate the score if we were to switch the lanes on current segment
        // if the switch would result in more potholes repaired - we store it in best
        if (auto current = calc_score_on_switch(L1[i], L2_current_potholes_count, L1_total_pothole_count,
                                                L1_current_potholes_count); current > best)
            best = current;
        if (auto current = calc_score_on_switch(L2[i], L1_current_potholes_count, L2_total_pothole_count,
                                                L2_current_potholes_count); current > best)
            best = current;
    }

    return best;
}

