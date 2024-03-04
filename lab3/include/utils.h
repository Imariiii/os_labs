#pragma once

#include <semaphore.h>

#include <cstddef>
#include <stdexcept>

inline constexpr int MAP_SIZE = sizeof(bool) + sizeof(float);
inline constexpr const char* SHARED_MEMORY_NAME = "shared_memory";

struct Slot {
    bool isEmpty;
    float num;
};