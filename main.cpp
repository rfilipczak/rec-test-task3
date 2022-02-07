#include <string>
#include <algorithm>
#include <iostream>


class Strategy
{
public:
    [[nodiscard]] virtual int solve(const std::string& L1, const std::string& L2) const = 0;

    virtual ~Strategy() = default;
};

class Solution
{
private:
    Strategy& strategy_;
public:
    explicit Solution(Strategy& strategy)
            : strategy_(strategy)
    {
    }

    void set_strategy(const Strategy& strategy)
    {
        this->strategy_ = strategy;
    }

    [[nodiscard]] int solve(const std::string& L1, const std::string& L2) const
    {
        return this->strategy_.solve(L1, L2);
    }
};

class BruteForceStrategy : public Strategy
{
private:
    static int count_potholes(const std::string& s)
    {
        return static_cast<int>(std::ranges::count(s, 'x'));
    }

    static int is_pothole(char c)
    {
        return c == 'x';
    }

    static int on_switch_score(char current_segment, int other_lane_current, int this_lane_total, int this_lane_current)
    {
        return this_lane_total - this_lane_current + other_lane_current - is_pothole(current_segment);
    }

public:
    [[nodiscard]] int solve(const std::string& L1, const std::string& L2) const override
    {
        auto L1_total_pothole_count = count_potholes(L1);
        auto L2_total_pothole_count = count_potholes(L2);

        int best = L1_total_pothole_count;

        int L1_current_potholes_count = 0;
        int L2_current_potholes_count = 0;

        for (size_t i = 1; i < L1.length(); ++i)
        {
            L1_current_potholes_count += is_pothole(L1[i - 1]);
            L2_current_potholes_count += is_pothole(L2[i - 1]);

            // now we calculate the score if we were to switch the lanes on current segment
            // if the switch would result in more potholes repaired - we store it in best
            if (auto current = on_switch_score(L1[i], L2_current_potholes_count, L1_total_pothole_count,
                                               L1_current_potholes_count); current > best)
                best = current;
            if (auto current = on_switch_score(L2[i], L1_current_potholes_count, L2_total_pothole_count,
                                               L2_current_potholes_count); current > best)
                best = current;
        }

        return best;
    }
};

template <typename ResultType>
static void show_result(ResultType got, ResultType expected)
{
    std::cout << (got == expected ? "[ PASSED ]" : "[ FAILED ]") << " Got: " << got << " expected: " << expected << '\n';
}

struct test_case
{
    const char* L1;
    const char* L2;
    int expected;
};

static int use(Solution& solution, const test_case& test_case)
{
    return solution.solve(test_case.L1, test_case.L2);
}

static void test_strategy(Strategy&& strategy)
{
    static const test_case stest_cases[] = {
            {"..xx.x.", "x.x.x..", 4},
            {".xxx...x", "..x.xxxx", 6},
            {"xxxxx", ".x..x", 5},
            {"x...x", "..x..", 2},
    };

    Solution solution(strategy);

    for (const auto& test : stest_cases)
        show_result(use(solution, test), test.expected);

}

int main()
{
    test_strategy(std::move(BruteForceStrategy()));
    return 0;
}
