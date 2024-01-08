#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
#include <map>

#define PAGE_SIZE 1024

struct Page{
    int blockSize;
    char* start;
    char* end;
};

class McKKAllocator {
private:
    std::vector<int> powsOf2 = {16, 32, 64, 128, 256, 512, 1024};
    std::vector<std::list<char*>> freeBlocksLists;
    std::vector<Page> kMemSize;
    char* data;
    
public:
    McKKAllocator(int pagesAmount, std::vector<int>& pagesFragments);
    
    void *Allocate(int bytesAmount);
    void DeAllocate(void *ptr);

    ~McKKAllocator();

};