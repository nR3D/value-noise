#ifndef SMOOTHSTEPNOISE_H
#define SMOOTHSTEPNOISE_H

float smoothstepInterpolation(float x, float p[2]);

float biSmoothstepInterpolation(float x, float y, float p[2][2]);

float smoothstepValueNoise(float x, float y, int anchor, float* lattice, int sizeLattice);

#endif
