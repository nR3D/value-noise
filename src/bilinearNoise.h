#ifndef BILINEARNOISE_H
#define BILINEARNOISE_H

float linearInterpolation(float x, float p[2]);

float bilinearInterpolation(float x, float y, float p[2][2]);

float bilinearValueNoise(float x, float y, int anchor, float* lattice, int sizeLattice);

#endif
