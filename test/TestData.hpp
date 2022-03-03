#ifndef TEST_DATA_H
#define TEST_DATA_H

#include <array>

namespace TestData
{
    struct TestCase
    {
        const char* L1;
        const char* L2;
        int expected;
    };

    const std::array<TestCase, 4> initialTests {{
            {"..xx.x.", "x.x.x..", 4},
            {".xxx...x", "..x.xxxx", 6},
            {"xxxxx", ".x..x", 5},
            {"x...x", "..x..", 2}
    }};

    const std::array<TestCase, 11> additionalTests {{
            {"...................", "xxxxxxxxxxxxxxxxxxx", 19},
            {"xxxxxxxxxxx", "xxxxxxxxxxx", 11},
            {"x", "x", 1},
            {"x", ".", 1},
            {".", ".", 0},
            {"..............", "..............", 0},
            {"x.x.x.x.x.x.x.", ".x.x.x.x.x.x.x", 7},
            {"x.x.x.x.x.x.x.", ".x.x.xxx.x.x.x", 8},
            {"xxxx...", "xx.x.xx", 6},
            {".....xxx..........", "xxx.........xxxxxx", 9},
            {".....xxx..........", "xxx.........xxxxxx", 9},
    }};
}

#endif
