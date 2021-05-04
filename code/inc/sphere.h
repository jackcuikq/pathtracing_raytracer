#ifndef SPHERE_H
#define SPHERE_H

#include "hittable_object.h"
#include "vec3.h"

class Sphere : public HittableObject {
	public:
		Sphere() {}
		Sphere(Point3 c, double r) : center(c), radius(r) {};

		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

		//members
		Point3 center;
		double radius;
};

#endif
