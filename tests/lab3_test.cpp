#include "lab3.h"

#include <gtest/gtest.h>

#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>

namespace fs = std::filesystem;

TEST(FirstLabTests, SimpleTest) {
    const char *childPath = getenv("PATH_TO_CHILD");
    ASSERT_TRUE(childPath);

    const std::string filenameInput = "in.txt";
    const std::string filenameTest = "test.txt";
    const std::string filenameOutput = "out.txt";

    constexpr int testSize = 5;
    constexpr int outputSize = testSize;

    const std::array<std::string, outputSize> testLines = {
        "10 1",
        "100 10",
        "",
        "1 9 9",
        "100 3 4 6",
    };

    const std::array<std::string, outputSize> expectedOutputLines = {
        "10",
        "10",
        "0",
        "0.0123457",
        "1.38889",
    };

    {
        auto input = std::ofstream(filenameInput);
        input << filenameTest << '\n';
        auto test = std::ofstream(filenameTest);
        for (const auto &line : testLines) {
            test << line << '\n';
        }
    }
    {
        auto input = std::ifstream(filenameInput);
        auto output = std::ofstream(filenameOutput);

        ParentRoutine(childPath, input, output);
    }
    auto output = std::ifstream(filenameOutput);

    std::string result;
    for (const std::string &line : expectedOutputLines) {
        std::getline(output, result);
        EXPECT_EQ(result, line);
    }

    auto removeIfExists = [](const std::string &path) {
        if (fs::exists(path)) {
            fs::remove(path);
        }
    };

    removeIfExists(filenameInput);
    removeIfExists(filenameTest);
    removeIfExists(filenameOutput);
}
