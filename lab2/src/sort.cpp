#include "sort.h"

#include <pthread.h>

#include <algorithm>
#include <iostream>
#include <vector>

std::size_t ParallelSort::Partition(std::vector<ll>& vec, std::size_t left,
                                    std::size_t right) {
    ll elem = vec[(left + right) / 2];
    while (left <= right) {
        while (vec[left] < elem) {
            ++left;
        }
        while (vec[right] > elem) {
            --right;
        }
        if (left >= right) {
            break;
        }
        std::swap(vec[left++], vec[right--]);
    }
    return right;
}

void ParallelSort::QuickSort(std::vector<ll>& vec, std::size_t left,
                             std::size_t right) {
    if (left < right) {
        std::size_t pivot = Partition(vec, left, right);
        QuickSort(vec, left, pivot);
        QuickSort(vec, pivot + 1, right);
    }
}

void* ParallelSort::QuickSort(void* ptr) {
    auto* args = static_cast<QuickSortArgs*>(ptr);
    QuickSort(*args->vec, args->left, args->right);
    return nullptr;
}

void ParallelSort::QuickSort(std::vector<ll>& vec, unsigned int threadsNum) {
    std::size_t numsPerThread = vec.size() / threadsNum;
    std::vector<pthread_t> threads(threadsNum);
    std::vector<QuickSortArgs> args(threadsNum);
    for (unsigned int i = 0; i < threadsNum; ++i) {
        std::size_t begin = i * numsPerThread;
        std::size_t end =
            (i == threadsNum - 1) ? vec.size() - 1 : begin + numsPerThread - 1;
        args[i] = {&vec, begin, end};
        pthread_create(&threads[i], nullptr, &QuickSort, &args[i]);
    }
    for (unsigned int i = 0; i < threadsNum; ++i) {
        pthread_join(threads[i], nullptr);
    }
    std::size_t step = numsPerThread;
    while (step < vec.size()) {
        for (std::size_t i = 0; i < vec.size() - step; i += 2 * step) {
            std::size_t left = i;
            std::size_t mid = i + step;
            std::size_t right = std::min<std::size_t>(i + 2 * step, vec.size());
            std::inplace_merge(vec.begin() + left, vec.begin() + mid,
                               vec.begin() + right);
        }
        step *= 2;
    }
}