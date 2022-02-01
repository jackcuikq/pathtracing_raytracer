# Path-tracing Raytracer

This is a brute force monte carlo pathtracer made with C++. Recreation of physical effects is done using simple linear algebra and physics (no API's or libraries used). Rendering only utilizes the CPU as images are rendered through calculations.

![a sample render](https://github.com/jackcuikq/simple_raytracer/blob/master/renders/main.jpg)

This render was done using 500 samples per pixel.

## Setup and Usage

Compilation can be done using the given ```CMakeLists.txt``` with cmake and creates an executable ```raytracer``` / ```raytracer.exe```. ```OpenMP``` was used for multithreading in speeding up rendering times and is included in ```CMakeLists.txt```. Though the pathtracer will still work without it, render times will be expected to take much longer.

The pathtracer writes a ```.ppm``` file with the render. 

```./raytracer.exe filename.ppm``` or ```./raytracer filename.ppm```

## Shapes and Materials

Currently the only shape with an implementation for ray surface intersection is spheres.

The materials implemented are Dielectric (refractive), Lambertian (matte) and Metal. 

![The materials](https://github.com/jackcuikq/simple_raytracer/blob/master/renders/sample_render.jpg)

(From left to right: Dielectric, Lambertian, Metal)

Dielectrics are clear materials like water or glass where when a light ray hits them, it splits into a reflected and refracted ray. In this implementation, only a single ray is scattered and it is chosen randomly if a ray reflects or refracts. A ray is refracted when possible according to Snell's law and when there is no solution the ray must reflect. Also, Schlick's approximation is used for approximating when to reflect.

Lambertian diffusion is done by picking a random vector in the hemisphere of the normal of the hit point and using it as the scattered ray.

For metals the ray isn't randomly scattered, it is reflected (using vector math).

## Other features

Anti-aliasing and denoising is done through taking repeated random samples of each pixel and averaging the colour of the rays. Increasing samples increases image quality but also greatly increases render time (especially for larger images). Though render times are reduced through multithreading, renders can still take a while.


## Resources

This project takes a lot from [this](https://raytracing.github.io/) book series which has given inspiration to add more features to this raytracer in the future.
