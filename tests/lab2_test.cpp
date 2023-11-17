#include <gtest/gtest.h>

#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <vector>
#include <thread>

#include "sort.h"

constexpr long long LEN = 1e6;

std::vector<long long> RandomVec(std::size_t len) {
    std::random_device rndDevice;
    std::mt19937 mersenneEngine{rndDevice()};
    std::uniform_int_distribution<long long> dist{
        std::numeric_limits<long long>::min(),
        std::numeric_limits<long long>::max()};
    auto gen = [&dist, &mersenneEngine]() { return dist(mersenneEngine); };
    std::vector<long long> vec(len);
    std::generate(std::begin(vec), std::end(vec), gen);
    return vec;
}

TEST(SecondLabTests, SimpleTest) {
    std::vector<long long> vec = {1,4,3, -13, 4};
    ParallelSort::QuickSort(vec, 5);
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(SecondLabTests, ReliabilityTest) {
    auto vec = RandomVec(LEN);
    ParallelSort::QuickSort(vec, 5);
    EXPECT_TRUE(std::is_sorted(vec.begin(), vec.end()));
}

TEST(SecondLabTests, MultithreadTest) {
    auto vec = RandomVec(LEN);
    unsigned int threadsNum = std::thread::hardware_concurrency();
    for (unsigned int i = 1; i < threadsNum; ++i) {
        auto vecCopy = vec;
        ParallelSort::QuickSort(vecCopy, i);
        EXPECT_TRUE(std::is_sorted(vecCopy.begin(), vecCopy.end()));
    }
}

TEST(SecondLabTests, EfficiencyTest) {
    auto vec = RandomVec(1e7);
    const unsigned int threadsNum = std::thread::hardware_concurrency();
    int64_t prevDuration = INT64_MAX;
    for (unsigned int i = 1; i < threadsNum; i+=(threadsNum> 2) ? threadsNum/3 : 1) {
        auto vecCopy = vec;
        auto start = std::chrono::high_resolution_clock::now();
        ParallelSort::QuickSort(vecCopy, i);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
        EXPECT_TRUE(std::is_sorted(vecCopy.begin(), vecCopy.end()));
        EXPECT_LT(duration, prevDuration);
        prevDuration = duration;
    }
}