#ifndef POW_ALLOCATOR_H
#define POW_ALLOCATOR_H
#include <stddef.h>

#define INIT_POW 5
#define NUM_OF_POWS 13


void PowInit();
void *PowAlloc(size_t size);
void PowFree(void *ptr);

#endif  // POW_ALLOCATOR_H