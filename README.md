# Value Noise Generator

Generate random value noise images, using different kinds of interpolation (bilinear, bicubic, and smoothstep). 

The graphical interface is based on Qt (v. 5.12), yet the value noise implementation (located in `src`) is independent of its GUI, hence it can be rewritten with any other graphic library.

!(screenSample)[images/screenSample.png]

## Interpolation

The value noise generation can also be extendend with other interpolations, as a matter of fact the function `valueNoise2d` (located in `src/valuenoise.h`) takes as one of its paramethers a function with the following signature:

``` float interpolation(float x, float y, int anchor, float* lattice, int sizeLattice) ```

where:
- `x` and `y` are values included on the interval \[0,1\] that rapresent the position of the interpoled point
- `anchor` is the index of the upper left value to be considered on `lattice`
- `lattice` is an array `sizeLattice`*`sizeLattice` filled with random values, and usually generated using the given function `float* vertexLattice(...)` (also located in `src/valuenoise.h`)
