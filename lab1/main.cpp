#include <cstdio>
#include <iostream>

#include "lab1.h"

int main() {
    const char *childPath = getenv("PATH_TO_CHILD");
    if (!childPath) {
        fprintf(stderr, "Set PATH_TO_CHILD\n");
        return -1;
    }
    ParentRoutine(childPath, std::cin, std::cout);
}