#ifndef SPHERE_H
#define SPHERE_H

#include "hittable_object.h"
#include "vec3.h"

class Sphere : public HittableObject {
	public:
		Sphere() {}
		Sphere(Point3 c, double r, std::shared_ptr<Material> m) : center(c), radius(r), mat(m) {};

		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

		//members
		Point3 center;
		double radius;
		std::shared_ptr<Material> mat;
};

#endif
