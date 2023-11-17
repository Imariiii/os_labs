#include "sort.h"

#include <pthread.h>

#include <algorithm>
#include <iostream>
#include <vector>

pthread_barrier_t barrier;

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
    auto& vec = *args->vec;
    QuickSort(vec, args->left, args->right);
    pthread_barrier_wait(&barrier);
    std::size_t step = args->numsPerThread;
    while (step < vec.size()) {
        if (args->id % 2 == 0) {
            args->id /= 2;
            std::size_t left = args->left;
            std::size_t mid =
                std::min<std::size_t>(args->left + step, vec.size());
            std::size_t right =
                std::min<std::size_t>(args->left + 2 * step, vec.size());
            std::inplace_merge(vec.begin() + left, vec.begin() + mid,
                               vec.begin() + right);
        }
        step *= 2;
        pthread_barrier_wait(&barrier);
    }
    return nullptr;
}

void ParallelSort::QuickSort(std::vector<ll>& vec, unsigned int threadsNum) {
    std::size_t numsPerThread;
    if (vec.size() < threadsNum) {
        numsPerThread = vec.size();
        threadsNum = 1;
    } else {
        numsPerThread = vec.size() / threadsNum;
    }
    std::vector<pthread_t> threads(threadsNum);
    std::vector<QuickSortArgs> args(threadsNum);
    pthread_barrier_init(&barrier, nullptr, threadsNum);
    for (unsigned int i = 0; i < threadsNum; ++i) {
        std::size_t begin = i * numsPerThread;
        std::size_t end =
            (i == threadsNum - 1) ? vec.size() - 1 : begin + numsPerThread - 1;
        args[i] = {&vec, begin, end, i, numsPerThread};
        pthread_create(&threads[i], nullptr, &QuickSort, &args[i]);
    }
    for (unsigned int i = 0; i < threadsNum; ++i) {
        pthread_join(threads[i], nullptr);
    }
    pthread_barrier_destroy(&barrier);
}