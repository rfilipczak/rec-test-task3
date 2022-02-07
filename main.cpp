#include <string>
#include <algorithm>
#include <iostream>
#include <memory>
#include <fstream>
#include <chrono>

class Strategy
{
public:
    [[nodiscard]] virtual int solve(const std::string& L1, const std::string& L2) const = 0;

    virtual ~Strategy() = default;
};

class Solution
{
private:
    std::unique_ptr<Strategy> strategy_;
public:
    explicit Solution(std::unique_ptr<Strategy> strategy)
            : strategy_(std::move(strategy))
    {
    }

    [[maybe_unused]] void set_strategy(std::unique_ptr<Strategy> strategy)
    {
        this->strategy_ = std::move(strategy);
    }

    [[nodiscard]] int solve(const std::string& L1, const std::string& L2) const
    {
        return this->strategy_->solve(L1, L2);
    }
};

/**
 * /brief O(N) I think... so not so brute-forcy after all
 */
class BruteForceStrategy : public Strategy
{
private:
    static std::array<int,2> count_potholes(const std::string& L1, const std::string& L2)
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

    static int is_pothole(char c)
    {
        return c == 'x';
    }

    static int calc_score_on_switch(char current_segment, int other_lane_current, int this_lane_total, int this_lane_current)
    {
        return this_lane_total - this_lane_current + other_lane_current - is_pothole(current_segment);
    }

public:
    [[nodiscard]] int solve(const std::string& L1, const std::string& L2) const override
    {
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
};

template <typename Strategy>
Solution solution_with()
{
    return Solution(std::make_unique<Strategy>());
}

template <typename ResultType>
static void show_result(const ResultType& got, const ResultType& expected)
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

static void test_brute_force_strategy()
{
    static const test_case stest_cases[] = {
            {"..xx.x.", "x.x.x..", 4},
            {".xxx...x", "..x.xxxx", 6},
            {"xxxxx", ".x..x", 5},
            {"x...x", "..x..", 2},
            {"...................", "xxxxxxxxxxxxxxxxxxx", 19}
    };

    auto solution = solution_with<BruteForceStrategy>();

    for (const auto& test : stest_cases)
        show_result(use(solution, test), test.expected);

    std::cout << "-- 200k test --" << '\n';
    std::string L1, L2;
    {
        std::fstream f{"./data.txt"};
        std::getline(f, L1);
    }

    {
        std::fstream f{"./data2.txt"};
        std::getline(f, L2);
    }

    using namespace std::chrono;

    auto start = high_resolution_clock::now();
    auto result = solution.solve(L1, L2);
    auto end = high_resolution_clock::now();

    std::cout << "Result for 200k chars = " << result << '\n';

    std::cout << "BruteForceStrategy for 200k chars took "
             << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "µs ≈ "
             << (end - start) / 1ms << "ms ≈ " // almost equivalent form of the above, but
             << (end - start) / 1s << "s.\n";  // using milliseconds and seconds accordingly
}

int main()
{
    test_brute_force_strategy();
    return 0;
}
