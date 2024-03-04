#include <stdlib.h>
#include <string.h>

#include "lib.h"
#include "utils.h"

#include <math.h>

char* Translation(long x) {
    if (x < 0) {
        return nullptr;
    }
    char* trinary = (char*)malloc(NUM_BUFFER_SIZE);
    if (!trinary) {
        return trinary;
    }
    int i = 0;
    do {
        trinary[i++] = '0' + (x % 3);
        x /= 3;
    } while (x);
    trinary[i] = '\0';
    ReverseString(trinary, i);
    return trinary;
}


float Derivative(float a, float deltaX) {
    return (cos(a + deltaX) - cos(a - deltaX)) / (2 * deltaX);
}
