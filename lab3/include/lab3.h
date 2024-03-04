#pragma once

#include <cstdio>
#include <iostream>

#define FILTER_LEN (11U)
#define MODE (0644U)

int ParentRoutine(const char* pathToChild, std::istream& streamIn, std::ostream& streamOut);