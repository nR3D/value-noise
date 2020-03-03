#ifndef VALUENOISE_H
#define VALUENOISE_H

#include <random>
#include <functional>

float* vertexLattice(int size, int amp, int yOffset, int seed);

float* valueNoise2d(int valueSize, int scale, int amp, int yOffset, float (*interpolation)(float,float,int,float*,int), int seed=0);

#endif
