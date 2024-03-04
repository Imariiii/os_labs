#pragma once

constexpr int NUM_BUFFER_SIZE = 33;

extern "C" {
char* Translation(long x);
float Derivative(float a, float deltaX);
}