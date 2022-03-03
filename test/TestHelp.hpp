#ifndef TEST_HELP_H
#define TEST_HELP_H

#include <fstream>
#include <string>

namespace testhelp
{
    void load_test_data(const char* path, std::string& in)
    {
        std::fstream f{path};
        std::getline(f, in);
    }
}

#endif
