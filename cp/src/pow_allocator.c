#include "pow_allocator.h"

#include <math.h>
#include <stdio.h>

struct Elem {
    void *ptr;
    char data[];
};

static void *HEADS[NUM_OF_POWS];
static char POOL[100000000];

void PowInit() {
    char *data = POOL;
    for (int i = 0; i < NUM_OF_POWS; ++i) {
        HEADS[i] = data;
        int pow = INIT_POW;
        size_t sizeofBlock = (1 << pow) + sizeof(void *);
        for (int j = 0; j < 100000; ++j) {
            ((struct Elem *)data)->ptr = data + sizeofBlock;
            data += sizeofBlock;
        }
        ((struct Elem *)data)->ptr = NULL;
        pow++;
        data += sizeofBlock;
    }
}

void *PowAlloc(size_t size) {
    int k;
    if (size < (1 << NUM_OF_POWS) + 1) {
        k = 0;
    } else {
        k = ceil(log2(size)) - INIT_POW;
    }
    struct Elem *temp = HEADS[k];
    HEADS[k] = temp->ptr;
    temp->ptr=HEADS+k;
    return temp->data;
}

void PowFree(void *ptr) {
    struct Elem *temp = (struct Elem *)((char*)ptr-sizeof(void*));
    void **headPtr = temp->ptr;
    temp->ptr = *headPtr;
    *headPtr = temp;
}