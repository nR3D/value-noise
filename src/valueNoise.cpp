#include "src/valueNoise.h"

float* vertexLattice(int size, int amp, int yOffset, int seed)
{
    // Returns float[size] filled with random values between (-amp,amp)+yOffset
    std::default_random_engine generator(seed);
    std::uniform_real_distribution<float> distribution(yOffset-amp,yOffset+amp);
    auto extract = std::bind (distribution, generator);
    float* vertex = new float[size*size];
    for(int i=0; i < size*size; i++)
	vertex[i] = extract();
    return vertex;
}

float* valueNoise2d(int valueSize, int scale, int amp, int yOffset, float (*interpolation)(float,float,int,float*,int), int seed)
{
    float* lattice = vertexLattice(valueSize+1, amp, yOffset, seed);
    float* grid = new float[valueSize*valueSize*scale*scale];
    for(int i=0; i < valueSize*valueSize*scale*scale; i++)
    {
	int anchor = (i%(valueSize*scale))/scale + (valueSize+1)*(i/(scale*scale*valueSize)); // index of the upper left vertex of lattice
	grid[i] = interpolation(static_cast<float>(i%scale)/(scale-1), static_cast<float>((i/(scale*valueSize))%scale)/(scale-1), anchor, lattice, valueSize+1);
    }
    delete[] lattice;
    return grid;
}
