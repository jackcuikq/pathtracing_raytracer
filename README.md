# Path-tracing Raytracer

This is a brute force monte carlo pathtracer made with C++ that executes on the CPU. Recreation of physical effects is done using simple linear algebra and physics 
(no API's or libraries used).

![a sample render](https://github.com/jackcuikq/simple_raytracer/blob/master/renders/main.jpg)

This render was done using 500 samples per pixel.

## Shapes and Materials

Currently the only shape with an implementation for ray surface intersection is spheres.

The materials implemented are Dielectric (refractive), Lambertian (matte) and Metal. 

![The materials](https://github.com/jackcuikq/simple_raytracer/blob/master/renders/sample_render.jpg)

(From left to right: Dielectric, Lambertian, Metal)

## Setup and Usage

Compilation can be done using the given ```CMakeLists.txt``` with cmake. ```OpenMP``` was used for multithreading in speeding up rendering times and is included in ```CMakeLists.txt```. Though the pathtracer will still work without it, render times will be expected to take much longer.

The pathtracer writes a ```.ppm``` file with the render. 

```./raytracer.exe >> "filename.ppm"``` or ```./raytracer >> "filename.ppm"```
