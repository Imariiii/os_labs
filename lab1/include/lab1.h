#pragma once
#include <iostream>

enum PipeEnd {
    READ_END,
    WRITE_END
};

void ParentRoutine(const char* pathToChild, std::istream& streamIn, std::ostream& streamOut);