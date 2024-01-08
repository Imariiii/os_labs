#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "utils.h"

#include <math.h>

char* Translation(long x) {
    if (x < 0) {
        return nullptr;
    }
    char* binary = (char*)malloc(NUM_BUFFER_SIZE);
    if (!binary) {
        return binary;
    }
    int i = 0;
    do {
        binary[i++] = '0' + (x & 1);
        x >>= 1;
    } while(x);
    binary[i] = '\0';
    ReverseString(binary, i);
    return binary;
}

float Derivative(float a, float deltaX) {
    return (cos(a + deltaX) - cos(a)) / deltaX;
}