#ifndef LAB1_H
#define LAB1_H

#include <iostream>

#define FILTER_LEN (11U)
#define MODE (0644U)

enum PipeEnd {
    READ_END,
    WRITE_END
};

void ParentRoutine(const char* pathToChild, std::istream& streamIn, std::ostream& streamOut);

#endif  // LAB1_H