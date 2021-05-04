#ifndef SPHERE_H
#define SPHERE_H

#include "hittable_object.h"
#include "vec3.h"

class sphere : public hittable_object {
	public:
		sphere() {}
		sphere(point3 c, double r) : center(c), radius(r) {};

		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

		//members
		point3 center;
		double radius;
};

#endif
