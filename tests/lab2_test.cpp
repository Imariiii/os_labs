#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <vector>
#include <thread>

#include "sort.h"

TEST(SecondLabTests, ReliabilityTest) {
    std::random_device rndDevice;
    std::mt19937 mersenneEngine{rndDevice()};
    std::uniform_int_distribution<long long> dist{
        std::numeric_limits<long long>::min(),
        std::numeric_limits<long long>::max()};
    auto gen = [&dist, &mersenneEngine]() { return dist(mersenneEngine); };
    std::vector<long long> vec(1e6);
    std::generate(std::begin(vec), std::end(vec), gen);
    ParallelSort::QuickSort(vec, std::thread::hardware_concurrency());
    ASSERT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(SecondLabTests, MultithreadTest) {
    std::random_device rndDevice;
    std::mt19937 mersenneEngine{rndDevice()};
    std::uniform_int_distribution<long long> dist{
        std::numeric_limits<long long>::min(),
        std::numeric_limits<long long>::max()};
    auto gen = [&dist, &mersenneEngine]() { return dist(mersenneEngine); };
    std::vector<long long> vec(1e6);
    std::generate(std::begin(vec), std::end(vec), gen);
    auto vecCopy = vec;
    ParallelSort::QuickSort(vec, 1);
    ParallelSort::QuickSort(vecCopy, std::thread::hardware_concurrency());
    ASSERT_TRUE(vec == vecCopy);
}