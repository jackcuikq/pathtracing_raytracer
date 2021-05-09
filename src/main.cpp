#include "utility.h"
#include "ray.h"
#include "colour.h"
#include "vec3.h"
#include "hittable_object_list.h"
#include "sphere.h"
#include "camera.h"
#include "material.h"

#include <iostream>
#include <chrono>

HittableObjectList random_scene() {
    HittableObjectList world;

    auto ground_material = std::make_shared<Lambertian>(Colour(0.5, 0.5, 0.5));
    world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = random_double();
            Point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if ((center - Point3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<Material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Colour::random() * Colour::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Colour::random(0.5, 1);
                    sphere_material = std::make_shared<Metal>(albedo);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Colour(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5));
    world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

    return world;
}

HittableObjectList simple_scene() {
    HittableObjectList world;

    auto material_ground = std::make_shared<Lambertian>(Colour(0.5, 0.5, 0.5));
    auto material_center = std::make_shared<Lambertian>(Colour(0.7, 0.3, 0.3));
    // auto material_left = std::make_shared<Metal>(Colour(0.8, 0.8, 0.8));
    auto material_left = std::make_shared<Dielectric>(1.5);
    auto material_right = std::make_shared<Metal>(Colour(0.8, 0.6, 0.2));

    world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
    world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
    world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
    world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

    return world;
}

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

int main() {

    const bool antialiasing = true;

    // Image

    const double aspect_ratio = 16.0 / 9.0;
    //const double aspect_ratio = 3.0 / 2.0;
    const int image_width = 2560;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 500;

    const int max_ray_depth = 50;

    // World

    //auto world = random_scene();
    auto world = simple_scene();

    // Camera
    
    Point3 lookfrom(3, 3, 5); // point looking from
    Point3 lookat(0, 0, 0); // point looking at
    Vec3 vup(0, 1, 0);
    double dist_to_focus = 10.0;
    double aperture = 0.1;
    double fov = 20; // lower FOV more zoomed in

    Camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

    // Render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

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

    auto stop = std::chrono::high_resolution_clock::now();
    auto render_time = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cerr << " Total render time ~" << render_time.count() << " seconds" << std::endl;
}

