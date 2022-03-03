cmake_minimum_required(VERSION 3.14)
project(task3)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    BruteForceStrategyTest
    ./test/BruteForceStrategyTest.cpp
    ./src/Solution.cpp
    ./src/BruteForceStrategy.cpp
)

add_executable(
    FailingStrategyTest
    ./test/FailingStrategyTest.cpp
    ./src/Solution.cpp
    ./src/FailingStrategy.cpp
)

target_link_libraries(
    BruteForceStrategyTest
    gtest_main
)

target_link_libraries(
    FailingStrategyTest
    gtest_main
)

include(GoogleTest)
gtest_discover_tests(BruteForceStrategyTest)
gtest_discover_tests(FailingStrategyTest)
