# Path-tracing Raytracer

This is a brute force raytracer/ pathtracer made with C++. For the path tracer, an attempt to recreate physical effects is done using simple linear algebra and physics 
(no API's or libraries used).

![a sample render](https://github.com/jackcuikq/simple_raytracer/blob/master/renders/main.jpg)

## Shapes and Materials

Currently the only shape with an implementation for ray surface intersection is spheres.

The materials implemented are Dielectric, Lambertian and Metal. 

![The materials](https://github.com/jackcuikq/simple_raytracer/blob/master/renders/sample_render.jpg)

(From left to right: Dielectric, Lambertian, Metal)
