#include "mck_allocator.h"

#include <sys/mman.h>
#include <unistd.h>

void MCKInit(struct MCKAllocator* a) {
    a->freePagesList = NULL;
    a->pageSize = getpagesize();
}

void MCKDestroy(struct MCKAllocator* a) {
    struct Page* curPage = a->freePagesList;

    while (curPage) {
        struct Page* toDelete = curPage;
        curPage = curPage->next;
        munmap(toDelete, a->pageSize);
        toDelete = NULL;
    }
    a->freePagesList = NULL;
}

void *MCKAlloc(struct MCKAllocator* a, size_t newblockSize) {

    size_t roundedBlockSize = 1;
    while (roundedBlockSize < newblockSize) {
        roundedBlockSize *= 2;
    }

    struct Page* curPage = a->freePagesList;

    while (curPage) {
        if (!curPage->isLarge &&
            curPage->blockSize == roundedBlockSize) {
            void* block = (void*)(curPage);
            a->freePagesList = curPage->next;

            return block;
        }

        curPage = curPage->next;
    }


    struct Page* newPage =
        (struct Page*)(mmap(NULL, a->pageSize, PROT_READ | PROT_WRITE,
                                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));

    if (newPage == MAP_FAILED) {
        return NULL;
    }
    newPage->isLarge = false;
    newPage->blockSize = roundedBlockSize;
    newPage->next = NULL;

    size_t numBlocks = a->pageSize / roundedBlockSize;
    for (size_t i = 0; i != numBlocks; ++i) {
        struct Page* blockPage = (struct Page*)(
            (char*)newPage + i * roundedBlockSize);
        blockPage->isLarge = false;
        blockPage->blockSize = roundedBlockSize;
        blockPage->next = a->freePagesList;
        a->freePagesList = blockPage;
    }

    void* block = (void*)(newPage);
    a->freePagesList = newPage->next;

    return block;
}

void MCKFree(struct MCKAllocator* a, void* block) {
    if (block == NULL) return;

    struct Page* page = (struct Page*)(block);
    page->next = a->freePagesList;
    a->freePagesList = page;
}