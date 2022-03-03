#include <memory>

#include <gtest/gtest.h>

#include "../include/Solution.hpp"
#include "../include/FailingStrategy.hpp"

#include "./TestData.hpp"


class FailingStrategyTest: public ::testing::Test
{
protected:
    Solution solution{std::make_unique<FailingStrategy>()};
};


TEST_F(FailingStrategyTest, FailsInitialTests)
{
    for (const auto& test : TestData::initialTests)
        EXPECT_NE(solution.solve(test.L1, test.L2), test.expected);
}

TEST_F(FailingStrategyTest, FailsAdditionallTests)
{
    for (const auto& test : TestData::additionalTests)
        EXPECT_NE(solution.solve(test.L1, test.L2), test.expected);
}

