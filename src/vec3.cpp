#include "vec3.h"

Vec3 random_in_unit_sphere() {
    while (true) {
        Vec3 p = Vec3::random(-1, 1);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

Vec3 random_unit_vector() {
    return unit_vector(random_in_unit_sphere());
}

Vec3 random_in_hemisphere(const Vec3& normal) {
    Vec3 rand_in_unit_sphere = random_in_unit_sphere();
    if (dot(rand_in_unit_sphere, normal) > 0.0) return rand_in_unit_sphere; // in same hemisphere as normal
    else return -rand_in_unit_sphere;
}

Vec3 random_in_unit_disk() {
    while (true) {
        Vec3 p = Vec3(random_double(-1, 1), random_double(-1, 1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

