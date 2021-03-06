#include <memory>
#include <chrono>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Solution.hpp"
#include "BruteForceStrategy.hpp"

#include "TestHelp.hpp"

class BruteForceStrategyTest : public ::testing::Test
{
protected:
    Solution solution{std::make_unique<BruteForceStrategy>()};
};


TEST_F(BruteForceStrategyTest, PassessInitialTests)
{
    EXPECT_EQ(solution.solve("..xx.x.", "x.x.x.."), 4);
    EXPECT_EQ(solution.solve(".xxx...x", "..x.xxxx"), 6);
    EXPECT_EQ(solution.solve("xxxxx", ".x..x"), 5);
    EXPECT_EQ(solution.solve("x...x", "..x.."), 2);
}

TEST_F(BruteForceStrategyTest, PassessAdditionalTests)
{
    EXPECT_EQ(solution.solve("...................", "xxxxxxxxxxxxxxxxxxx"), 19);
    EXPECT_EQ(solution.solve("xxxxxxxxxxx", "xxxxxxxxxxx"), 11);
    EXPECT_EQ(solution.solve("x", "x"), 1);
    EXPECT_EQ(solution.solve("x", "."), 1);
    EXPECT_EQ(solution.solve(".", "."), 0);
    EXPECT_EQ(solution.solve("..............", ".............."), 0);
    EXPECT_EQ(solution.solve("x.x.x.x.x.x.x.", ".x.x.x.x.x.x.x"), 7);
    EXPECT_EQ(solution.solve("x.x.x.x.x.x.x.", ".x.x.xxx.x.x.x"), 8);
    EXPECT_EQ(solution.solve("xxxx...", "xx.x.xx"), 6);
    EXPECT_EQ(solution.solve(".....xxx..........", "xxx.........xxxxxx"), 9);
}

TEST_F(BruteForceStrategyTest, IsFastEnough)
{
    std::string L1 = testhelp::generateRandomStringFromSet(200'000, ".x");
    std::string L2 = testhelp::generateRandomStringFromSet(200'000, ".x");
    
    ASSERT_EQ(L1.length(), 200'000);
    ASSERT_EQ(L2.length(), 200'000);

    using namespace std::chrono;

    auto start = high_resolution_clock::now();
    auto result = solution.solve(L1, L2);
    auto end = high_resolution_clock::now();

    using ::testing::AllOf;
    using ::testing::Le;
    using ::testing::Gt;
    ASSERT_THAT(result, AllOf(Gt(0), Le(200'000)));

    auto time = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
    EXPECT_LT(time, 1);
}
