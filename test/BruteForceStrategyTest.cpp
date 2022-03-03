#include <memory>

#include <gtest/gtest.h>

#include "../include/Solution.hpp"
#include "../include/BruteForceStrategy.hpp"

#include "./TestData.hpp"

class BruteForceStrategyTest : public ::testing::Test
{
protected:
    Solution solution{std::make_unique<BruteForceStrategy>()};
};


TEST_F(BruteForceStrategyTest, PassessInitialTests)
{
    for (const auto& test : TestData::initialTests)
        EXPECT_EQ(solution.solve(test.L1, test.L2), test.expected);
}

TEST_F(BruteForceStrategyTest, PassessAdditionalTests)
{
    for (const auto& test : TestData::additionalTests)
        EXPECT_EQ(solution.solve(test.L1, test.L2), test.expected);
}

