#include <iostream>
#include <list>
#include <vector>

class TPow2Allocator {
private:
    std::vector<std::list<char*>> freeBlocksLists;
    std::vector<int> powsOf2 = {16, 32, 64, 128, 256, 512, 1024};
    char* data;
    
public:
    TPow2Allocator(std::vector<int>& blocksAmount);

    void *Allocate(int bytesAmount);
    void DeAllocate(void *ptr);
    ~TPow2Allocator();
};