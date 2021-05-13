#ifndef SAMPLE_RENDERS_H
#define SAMPLE_RENDERS_H

# include "hittable_object_list.h"

namespace SampleRenders {
    /* Camera settings
        Point3 lookfrom(10, 3, 10); // point looking from
        Point3 lookat(0, 0, -1); // point looking at
        Vec3 vup(0, 1, 0);
        double dist_to_focus = 14.0;
        double aperture = 0;
        double fov = 20; // lower FOV more zoomed in
    */
    HittableObjectList main_scene() {
        HittableObjectList world;

        auto ground_material = std::make_shared<Metal>(Colour(0.6, 0.4, 1));
        world.add(std::make_shared<Sphere>(Point3(0, -1000, 0), 1000, ground_material));

        // far left
        auto material1 = std::make_shared<Lambertian>(Colour(0, 1, 1));
        world.add(std::make_shared<Sphere>(Point3(-2.5, 1, 0), 1.0, material1));

        auto material2 = std::make_shared<Dielectric>(1.5);
        world.add(std::make_shared<Sphere>(Point3(2, 0.75, 0), 0.75, material2));

        // far right
        auto material3 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5));
        world.add(std::make_shared<Sphere>(Point3(4, 1, 0), 1.0, material3));

        auto material4 = std::make_shared<Metal>(Colour(0.7, 0.6, 0.5));
        world.add(std::make_shared<Sphere>(Point3(-1, 1.5, -3), 1.5, material4));

        auto material5 = std::make_shared<Lambertian>(Colour(0.7, 0.5, 0.5));
        world.add(std::make_shared<Sphere>(Point3(-0.5, 0.5, 0), 0.5, material5));

        auto material6 = std::make_shared<Lambertian>(Colour(0.7, 0.5, 0.2));
        world.add(std::make_shared<Sphere>(Point3(0, 0.5, -1), 0.5, material6));

        auto material7 = std::make_shared<Lambertian>(Colour(0.3, 0.5, 0.2));
        world.add(std::make_shared<Sphere>(Point3(3, 0.5, 4), 0.5, material7));

        return world;
    }

    HittableObjectList simple_scene() {
        HittableObjectList world;

        auto material_ground = std::make_shared<Lambertian>(Colour(0.5, 0.5, 0.5));
        auto material_center = std::make_shared<Lambertian>(Colour(0.7, 0.3, 0.4));
        // auto material_left = std::make_shared<Metal>(Colour(0.8, 0.8, 0.8));
        auto material_left = std::make_shared<Dielectric>(1.5);
        auto material_right = std::make_shared<Metal>(Colour(0.7, 0.6, 0.2));

        world.add(std::make_shared<Sphere>(Point3(0.0, -100.5, -1.0), 100.0, material_ground));
        world.add(std::make_shared<Sphere>(Point3(0.0, 0.0, -1.0), 0.5, material_center));
        world.add(std::make_shared<Sphere>(Point3(-1.0, 0.0, -1.0), 0.5, material_left));
        world.add(std::make_shared<Sphere>(Point3(1.0, 0.0, -1.0), 0.5, material_right));

        return world;
    }
}

#endif
