#ifndef HITTABLE_OBJECT_H
#define HITTABLE_OBJECT_H

#include "ray.h"

struct HitRecord {
	Point3 p;
	Vec3 normal;
	double t;
	bool front_face;

	inline void set_face_normal(const Ray& r, const Vec3& outward_normal) {
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

// abstract class for hittable objects
class HittableObject {
	public:
		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const = 0;
};

#endif
