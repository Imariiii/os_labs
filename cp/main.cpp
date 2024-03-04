
#include <unistd.h>

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <vector>

extern "C" {
#include "mck_allocator.h"
#include "pow_allocator.h"
}
size_t page_size = sysconf(_SC_PAGESIZE);

static void benchmark(struct MCKAllocator* MCKAlloctor, std::size_t size,
                      std::size_t n) {
    PowInit();
    MCKInit(MCKAlloctor);
    std::vector<void*> list_blocks;
    std::vector<void*> MKC_blocks;

    std::cout << "Comparing PowAllocator and MCKAllocator" << std::endl;

    std::cout << "Block allocation rate of " << n << " chunks of " << size
              << " bytes" << std::endl;
    auto start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != n; ++i) {
        void* block = PowAlloc(size);
        list_blocks.push_back(block);
    }
    auto end_time = std::chrono::steady_clock::now();
    std::cout << "Time of alloc PowAllocator: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " milliseconds" << std::endl;

    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != n; ++i) {
        void* block = MCKAlloc(MCKAlloctor, size);
        MKC_blocks.push_back(block);
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of alloc MCKAllocator: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " milliseconds" << std::endl;

    std::cout << "Block free rate" << std::endl;
    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != list_blocks.size(); ++i) {
        PowFree(list_blocks[i]);
    }
    end_time = std::chrono::steady_clock::now();
    std::cout << "Time of free PowAllocator: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " milliseconds" << std::endl;

    start_time = std::chrono::steady_clock::now();
    for (size_t i = 0; i != MKC_blocks.size(); ++i) {
        MCKFree(MCKAlloctor, MKC_blocks[i]);
    }
    end_time = std::chrono::steady_clock::now();

    std::cout << "Time of free MCKAllocator: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     end_time - start_time)
                     .count()
              << " milliseconds" << std::endl;
}

int main() {
    MCKAllocator a;

    for (size_t i = 0; i < 10; ++i)
    benchmark(&a, 100*(i+1), 70000);

    /* for (size_t i = 0; i < 10; ++i)
    benchmark(&a, 1000*(i+1), 70000); */

   /*  for (size_t i = 0; i < 12; ++i)
    benchmark(&a, 10000*(i+1), 70000); */

    std::cout << "-----------------------";
    for (size_t i = 0; i < 5; ++i)
    benchmark(&a, 1000, 10000*(i+1));


}