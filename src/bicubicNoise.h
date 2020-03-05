#ifndef BICUBICNOISE_H
#define BICUBICNOISE_H

#include <iostream>

inline int divF(int, int);

float cubicIterpolation(float x, float p[4]);

float bicubicInterpolation(float x, float y, float p[4][4]);

float bicubicValueNoise(float x, float y, int anchor, float* lattice, int sizeLattice);

#endif
