#include "pow_of_two_allocator.h"

TPow2Allocator::TPow2Allocator(std::vector<int>& blocksAmount){
    freeBlocksLists = std::vector<std::list<char*>>(powsOf2.size());
    int bytesSum = 0;
    for (long unsigned int i = 0; i < blocksAmount.size(); ++i){
        bytesSum += blocksAmount[i] * powsOf2[i];
    }
    data = (char*)malloc(bytesSum);
    char* dataCopy = data;
    for (long unsigned int i = 0; i < blocksAmount.size(); ++i){
        for (int j = 0; j < blocksAmount[i]; ++j){
            freeBlocksLists[i].push_back(dataCopy);
            *((int*)dataCopy) = powsOf2[i];
            dataCopy += powsOf2[i];
        }
    }

}

void* TPow2Allocator::Allocate(int bytesAmount){
    if (bytesAmount == 0){
        return nullptr;
    }
    bytesAmount += sizeof(int);
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
    return (void*)(memory + sizeof(int));
}

void TPow2Allocator::DeAllocate(void* ptr){
    char* chPtr = (char*)ptr;
    chPtr = chPtr - sizeof(int);
    int blockSize = *((int*)chPtr);
    int ind = -1;
    for(long unsigned int i = 0; i < powsOf2.size(); ++i){
        if(powsOf2[i] == blockSize){
            ind = i;
        }
    }

    freeBlocksLists[ind].push_back(chPtr);
}

TPow2Allocator::~TPow2Allocator(){
    std::cout << "In destructor\n";
    free(data);
}