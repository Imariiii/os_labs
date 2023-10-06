#include <gtest/gtest.h>

extern "C" {
#include "lab1.h"
}

#include <array>
#include <filesystem>
#include <fstream>
#include <memory>

namespace fs = std::filesystem;

TEST(FirstLabTests, SimpleTest) {
    ASSERT_TRUE(true);
}