#include "smoothstepNoise.h"

float smoothstepInterpolation(float x, float p[2])
{
    if(x > 1) x = 1;
    else if(x < 0) x = 0;
    return x*x*x*(6*x*x - 15*x +10)*(p[1]-p[0]) + p[0];
}

float biSmoothstepInterpolation(float x, float y, float p[2][2])
{
    float arr[2];
    arr[0] = smoothstepInterpolation(x, p[0]);
    arr[1] = smoothstepInterpolation(x, p[1]);
    return smoothstepInterpolation(y, arr);
}

float smoothstepValueNoise(float x, float y, int anchor, float* lattice, int sizeLattice)
{
    float arr[2][2] = {{lattice[anchor], lattice[anchor+1]}, {lattice[anchor+sizeLattice], lattice[anchor+sizeLattice+1]}};
    return biSmoothstepInterpolation(x, y, arr);
}
