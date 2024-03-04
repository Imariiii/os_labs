#ifndef POW_ALLOCATOR_H
#define MCK_ALLOCATOR_H
#include <stddef.h>
#include <stdbool.h>

struct Page {
    struct Page* next;
    bool isLarge;
    size_t blockSize;
};

struct MCKAllocator {
    struct Page* freePagesList;
    size_t pageSize;
};

void MCKInit(struct MCKAllocator* a);
void MCKDestroy(struct MCKAllocator* a);
void *MCKAlloc(struct MCKAllocator* a, size_t newblockSize);
void MCKFree(struct MCKAllocator* a, void* block);
#endif  // MCK_ALLOCATOR_H