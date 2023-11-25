#include <algorithm>
#include <chrono>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

#include "sort.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "usage: sort THREADS\n";
        std::exit(EXIT_SUCCESS);
    }
    std::random_device rndDevice;
    std::mt19937 mersenneEngine{rndDevice()};
    std::uniform_int_distribution<long long> dist{
        std::numeric_limits<long long>::min(),
        std::numeric_limits<long long>::max()};
    auto gen = [&dist, &mersenneEngine]() { return dist(mersenneEngine); };
    std::vector<long long> vec(1e7);
    std::generate(std::begin(vec), std::end(vec), gen);
    for (unsigned int i = 1;
         i < static_cast<unsigned int>(std::stoi(argv[1])+1); ++i) {
        auto vecCopy = vec;
        auto start = std::chrono::high_resolution_clock::now();
        ParallelSort::QuickSort(vecCopy, i);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration =
            std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        if (std::is_sorted(vecCopy.begin(), vecCopy.end())) {
            std::cout << "Sorted on " << i << " threads in " << duration.count()
                      << "ms" << std::endl;
        } else {
            std::cout << "Something wrong" << std::endl;
        }
    }
    return 0;
}