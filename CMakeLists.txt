cmake_minimum_required(VERSION 3.22)
project(task3)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "-Wpedantic -Wall -Wextra" CACHE STRING "")

include(FetchContent)


# From Official gtest quickstart...
# FetchContent_Declare(
#     googletest
#     URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
# )

# FetchContent_MakeAvailable(googletest)

# https://modern-cmake-cn.github.io/Modern-CMake-zh_CN/chapters/testing/googletest.html
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.11.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()


enable_testing()

include_directories(
    ./test
    ./include
)


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
    gmock_main
)

target_link_libraries(
    FailingStrategyTest
    gtest_main
)


include(GoogleTest)
gtest_discover_tests(BruteForceStrategyTest)
gtest_discover_tests(FailingStrategyTest)
