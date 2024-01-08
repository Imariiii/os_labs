#include "mck-k.h"

McKKAllocator::McKKAllocator(int pagesAmount, std::vector<int>& pagesFragments){

    freeBlocksLists = std::vector<std::list<char*>>(powsOf2.size());
    data = (char*)malloc(pagesAmount * PAGE_SIZE);
    char* curPageStart = data;
    char* curPageEnd = curPageStart + (PAGE_SIZE - 1);
    kMemSize = std::vector<Page>(pagesAmount);

    for(int i = 0; i < pagesAmount; ++i){
        kMemSize[i].blockSize = pagesFragments[i];
        kMemSize[i].start = curPageStart;
        kMemSize[i].end = curPageEnd;
        curPageStart += PAGE_SIZE;
        curPageEnd += PAGE_SIZE;
    }

    for (long unsigned int i = 0; i < kMemSize.size(); ++i){
        int ind = -1;
        for(long unsigned int j = 0; j < powsOf2.size(); ++j){
            if(kMemSize[i].blockSize == powsOf2[j]){
                ind = j;
                break;
            }
        }
        char* curBlockStart = kMemSize[i].start;
        for(int j = 0; j < PAGE_SIZE / kMemSize[i].blockSize; ++j){
            freeBlocksLists[ind].push_back(curBlockStart);
            curBlockStart += kMemSize[i].blockSize;
        }
        
    }
}

void* McKKAllocator::Allocate(int bytesAmount){
    if (bytesAmount == 0){
        return nullptr;
    }
    int ind = -1;
    for (long unsigned int i = 0; i < freeBlocksLists.size(); ++i){
        if (bytesAmount <= powsOf2[i] && !freeBlocksLists[i].empty()){
            ind = i;
            break;
        }
    }
    if (ind == -1){
        std::cout << "There isn't memory\n";
    }

    char* memory = freeBlocksLists[ind].front();
    freeBlocksLists[ind].pop_front();
    return (void*)memory;
}

void McKKAllocator::DeAllocate(void* ptr){
    char *chPtr = (char*)ptr;

    int indPage = -1;
    for(long unsigned int i = 0; i < kMemSize.size(); ++i){
        if(kMemSize[i].start <= chPtr && chPtr <= kMemSize[i].end){
            indPage = i;
            break;
        }
    }

    int indBlock = -1;
    for(long unsigned int j = 0; j < powsOf2.size(); ++j){
        if(kMemSize[indPage].blockSize == powsOf2[j]){
            indBlock = j;
            break;
        }
    }

    freeBlocksLists[indBlock].push_back(chPtr);
}

McKKAllocator::~McKKAllocator(){
    std::cout << "In destructor1\n";
    free(data);
}