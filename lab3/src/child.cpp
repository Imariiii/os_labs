#include <unistd.h>

#include <iostream>
#include <sstream>
#include <string>

#include "shared_memory.h"
#include "utils.h"

int main() {
    std::string line;
    WeakSharedMemory<Slot> shm(SHARED_MEMORY_NAME);
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        float dividend;
        if (!(iss >> dividend)) {
            dividend = 0;
        }
        float divisor;
        while (iss >> divisor) {
            dividend /= divisor;
            if (divisor == 0) {
                shm.writeLock();
                shm.getData()->isEmpty = false;
                shm.getData()->num = dividend;
                shm.readUnlock();
                return -1;
            }
        }
        shm.writeLock();
        shm.getData()->isEmpty = false;
        shm.getData()->num = dividend;
        shm.readUnlock();
    }
    shm.writeLock();
    shm.getData()->isEmpty = true;
    shm.readUnlock();
    return 0;
}