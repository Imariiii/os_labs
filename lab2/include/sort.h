#pragma once
#include <vector>

class ParallelSort {
    using ll = long long;

   public:
    static void QuickSort(std::vector<ll>& vec, unsigned int threadsNum);

   private:
    struct QuickSortArgs {
        std::vector<ll>* vec;
        std::size_t left;
        std::size_t right;
        unsigned int id;
        std::size_t numsPerThread;
    };

    static void* QuickSort(void* ptr);
    static void QuickSort(std::vector<ll>& vec, std::size_t left,
                          std::size_t right);
    static std::size_t Partition(std::vector<ll>& vec, std::size_t left,
                                 std::size_t right);
};