#ifndef TEST_HELP_H
#define TEST_HELP_H

#include <fstream>
#include <string>
#include <random>

namespace testhelp
{
    std::string generateRandomStringFromSet(const std::size_t length, const std::string& set)
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0, set.size() - 1);

        std::string retval;

        std::generate_n(std::back_inserter(retval), length, [&]()
        {
            return set[distribution(generator)];
        });

        return retval;
    }
}

#endif
