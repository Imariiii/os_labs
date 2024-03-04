#include <cstdlib>
#include <iostream>

#include "lab3.h"

int main() {
    const char *childPath = getenv("PATH_TO_CHILD");
    if (!childPath) {
        std::cerr << "Set environment variable PATH_TO_CHILD\n";
        std::exit(EXIT_FAILURE);
    }
    return ParentRoutine(childPath, std::cin, std::cout);
}