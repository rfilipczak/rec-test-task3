#include <memory>

#include <gtest/gtest.h>

#include "Solution.hpp"
#include "FailingStrategy.hpp"


class FailingStrategyTest: public ::testing::Test
{
protected:
    Solution solution{std::make_unique<FailingStrategy>()};
};


TEST_F(FailingStrategyTest, FailsInitialTests)
{
    EXPECT_NE(solution.solve("..xx.x.", "x.x.x.."), 4);
    EXPECT_NE(solution.solve(".xxx...x", "..x.xxxx"), 6);
    EXPECT_NE(solution.solve("xxxxx", ".x..x"), 5);
    EXPECT_NE(solution.solve("x...x", "..x.."), 2);
}

TEST_F(FailingStrategyTest, FailsAdditionallTests)
{
    EXPECT_NE(solution.solve("...................", "xxxxxxxxxxxxxxxxxxx"), 19);
    EXPECT_NE(solution.solve("xxxxxxxxxxx", "xxxxxxxxxxx"), 11);
    EXPECT_NE(solution.solve("x", "x"), 1);
    EXPECT_NE(solution.solve("x", "."), 1);
    EXPECT_NE(solution.solve(".", "."), 0);
    EXPECT_NE(solution.solve("..............", ".............."), 0);
    EXPECT_NE(solution.solve("x.x.x.x.x.x.x.", ".x.x.x.x.x.x.x"), 7);
    EXPECT_NE(solution.solve("x.x.x.x.x.x.x.", ".x.x.xxx.x.x.x"), 8);
    EXPECT_NE(solution.solve("xxxx...", "xx.x.xx"), 6);
    EXPECT_NE(solution.solve(".....xxx..........", "xxx.........xxxxxx"), 9);
}

