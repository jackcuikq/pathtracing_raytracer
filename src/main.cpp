#include "utility.h"
#include "ray.h"
#include "colour.h"
#include "vec3.h"
#include "hittable_object_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"
#include "sample_renders.h"

#include <iostream>
#include <fstream>
#include <chrono>

Colour ray_colour(const Ray& r, const HittableObject& world, int depth) {
    HitRecord rec;

    // if ray bounce limit is exceeded, no more light is gathered
    if (depth <= 0) return Colour(0, 0, 0);

    if (world.hit(r, 0.005, infinity, rec)) {
        Ray scattered;
        Colour attenuation;
        if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
            return attenuation * ray_colour(scattered, world, depth - 1);
        return Colour(0, 0, 0);
    }
 
    Vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * Colour(1.0, 1.0, 1.0) + t * Colour(0.5, 0.7, 1.0);
}

int main(int argc, char* argv[]) {
    // no file given
    if (argc <= 1) {
        std::cerr << "No file given" << '\n';
        return 0;
    }

    // open file
    std::ofstream outfile;
    outfile.open(argv[1]);
    if (!outfile) {
        std::cerr << "Fail to open file for write" << '\n';
    }

    const bool antialiasing = true;

    // Image

    //const double aspect_ratio = 16.0 / 9.0;
    const double aspect_ratio = 3.0 / 2.0;
    const int image_width = 800;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 500;

    const int max_ray_depth = 50;

    // World

    //auto world = SampleRenders::main_scene();
    auto world = SampleRenders::simple_scene();

    // Camera
    
    Point3 lookfrom(0, 0, 6); // point looking from
    Point3 lookat(0, 0, -1); // point looking at
    Vec3 vup(0, 1, 0);
    double dist_to_focus = 6;
    double aperture = 0;
    double fov = 20; // lower FOV more zoomed in

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    // Render

    outfile << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    auto start = std::chrono::high_resolution_clock::now();

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            if (antialiasing) {
                Colour pixel_colour(0, 0, 0);

                // Use multi-threading for calculating samples per pixel
                #pragma omp parallel for
                for (int s = 0; s < samples_per_pixel; ++s) {
                    double u = (i + random_double()) / (image_width - 1);
                    double v = (j + random_double()) / (image_height - 1);
                    Ray r = cam.get_ray(u, v);

                    Colour ray_col = ray_colour(r, world, max_ray_depth);

                    #pragma omp atomic
                    pixel_colour.e[0] += ray_col.x();

                    #pragma omp atomic
                    pixel_colour.e[1] += ray_col.y();

                    #pragma omp atomic
                    pixel_colour.e[2] += ray_col.z();
                }
                write_colour(outfile, pixel_colour, samples_per_pixel);
            } else {
                double u = double(i) / (image_width - 1);
                double v = double(j) / (image_height - 1);
                Ray r = cam.get_ray(u, v);                
                Colour pixel_color = ray_colour(r, world, max_ray_depth);
                write_colour(outfile, pixel_color, 1);
            }
        }
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto render_time = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cerr << " Total render time ~" << render_time.count() << " seconds" << std::endl;
}

