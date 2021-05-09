#include "utility.h"
#include "ray.h"
#include "colour.h"
#include "vec3.h"
#include "hittable_object_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <iostream>

Colour ray_colour(const Ray& r, const HittableObject& world, int depth) {
    HitRecord rec;

    // if ray bounce limit is exceeded, no more light is gathered
    if (depth <= 0) return Colour(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec)) {
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

int main() {

    const bool antialiasing = true;

    // Image

    const auto aspect_ratio = 16.0 / 9.0;
    // 400
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;

    const int max_ray_depth = 50;

    // World
    
    HittableObjectList world;

    auto material_ground = std::make_shared<Lambertian>(Colour(0.8, 0.8, 0.0));
    auto material_center = std::make_shared<Lambertian>(Colour(0.7, 0.3, 0.3));
    // auto material_left = std::make_shared<Metal>(Colour(0.8, 0.8, 0.8));
    auto material_left = std::make_shared<Dielectric>(1.5);
    auto material_right = std::make_shared<Metal>(Colour(0.8, 0.6, 0.2));

    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

    // Camera

    Camera cam;

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = image_height - 1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            if (antialiasing) {
                Colour pixel_colour(0, 0, 0);
                for (int s = 0; s < samples_per_pixel; ++s) {
                    double u = (i + random_double()) / (image_width - 1);
                    double v = (j + random_double()) / (image_height - 1);
                    Ray r = cam.get_ray(u, v);
                    pixel_colour += ray_colour(r, world, max_ray_depth);
                }
                write_colour(std::cout, pixel_colour, samples_per_pixel);
            } else {
                double u = double(i) / (image_width - 1);
                double v = double(j) / (image_height - 1);
                Ray r = cam.get_ray(u, v);                
                Colour pixel_color = ray_colour(r, world, max_ray_depth);
                write_colour(std::cout, pixel_color, 1);
            }
        }
    }

    std::cerr << "\nDone.\n";
}
