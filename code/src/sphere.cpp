#include "sphere.h"

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
    // calculate variables to get discriminant
    vec3 oc = r.origin() - center;
    double a = r.direction().length_squared();
    double half_b = dot(oc, r.direction());
    double c = oc.length_squared() - radius * radius;

    double discriminant = half_b * half_b - a * c;
    if (discriminant < 0) return false;
    double disc_sqrt = sqrt(discriminant);

    // Find the root that lies in acceptable range
    double curr_root = (-half_b - disc_sqrt) / a;
    if (curr_root < t_min || t_max < curr_root) {
        // try other root
        curr_root = (-half_b + disc_sqrt) / a;
        if (curr_root < t_min || t_max < curr_root) {
            return false;
        }
    }

    // record data
    rec.t = curr_root;
    rec.p = r.at(rec.t);

    vec3 outward_normal = (rec.p - center) / radius;
    rec.set_face_normal(r, outward_normal);

    return true;
}
