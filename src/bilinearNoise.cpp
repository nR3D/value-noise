#include "bilinearNoise.h"

float linearInterpolation(float x, float p[2])
{
    return p[1]*x + p[0]*(1-x);
}

float bilinearInterpolation(float x, float y, float p[2][2])
{
    float arr[2];
    arr[0] = linearInterpolation(x, p[0]);
    arr[1] = linearInterpolation(x, p[1]);
    return linearInterpolation(y, arr);
}

float bilinearValueNoise(float x, float y, int anchor, float* lattice, int sizeLattice)
{
    float arr[2][2] = {{lattice[anchor], lattice[anchor+1]}, {lattice[anchor+sizeLattice], lattice[anchor+sizeLattice+1]}};
    return bilinearInterpolation(x, y, arr);
}
