#include "src/bicubicNoise.h"

inline int divF(int a, int b)
{
    // return a/b, but the result will always be rounded to the lower integer
    return a*b < 0 ? a/b-1 : a/b;
}

float cubicInterpolation(float x, float p[4])
{
    return p[1] + 0.5*x*(p[2] - p[0] + x*(2.0*p[0] - 5.0*p[1] + 4.0*p[2] - p[3] + x*(3.0*(p[1] - p[2]) + p[3] - p[0])));
}

float bicubicInterpolation(float x, float y, float p[4][4])
{
    float arr[4];
    arr[0] = cubicInterpolation(x, p[0]);
    arr[1] = cubicInterpolation(x, p[1]);
    arr[2] = cubicInterpolation(x, p[2]);
    arr[3] = cubicInterpolation(x, p[3]);
    return cubicInterpolation(y, arr);
}

float bicubicValueNoise(float x, float y, int anchor, float* lattice, int sizeLattice)
{
    float arr[4][4];
    for(int i=0; i < 16; i++)
    {
	int vertex;
	if(i/4-1 + anchor/sizeLattice >= 0)
	{
	    vertex = anchor-1 + i%4 + sizeLattice*(i/4-1);
	    if(i/4 > sizeLattice - anchor/sizeLattice)
        vertex -= sizeLattice*(i/4 - sizeLattice + anchor/sizeLattice);
	}
	else
	    vertex = anchor-1+i;
	if(i%4==0 && divF(vertex, sizeLattice) != divF(vertex+1, sizeLattice))
	    ++vertex;
	else if(i%4==3 && divF(vertex, sizeLattice) != divF(vertex-1, sizeLattice))
	    --vertex;
    arr[i/4][i%4] = lattice[vertex];
    }
    return bicubicInterpolation(x, y, arr);
}
