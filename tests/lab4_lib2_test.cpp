#include <gtest/gtest.h>

#include <cstring>
#include <utility>

#include "lib.h"

constexpr const float EPS = 1e-6;
constexpr const float PI = 3.14159265359;

bool EqualFloat(float lhs, float rhs) {
    return std::abs(lhs - rhs) < EPS;
}

TEST(FourthLabTests, DerivativeTest) {
    EXPECT_TRUE(EqualFloat(Derivative(PI, EPS), 0));
}

TEST(FourthLabTests, TranslationTest) {
    auto deleter = [](char *str) { std::free(str); };
    std::unique_ptr<char, decltype(deleter)> str(Translation(0), deleter);
    EXPECT_TRUE(std::strcmp(str.get(), "0") == 0);
    str.reset(Translation(5));
    EXPECT_TRUE(std::strcmp(str.get(), "12") == 0);
    str.reset(Translation(888));
    EXPECT_TRUE(std::strcmp(str.get(), "1012220") == 0);
    str.reset(Translation(-1));
    EXPECT_EQ(str.get(), nullptr);
}