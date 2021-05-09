#include "hittable_object_list.h"

bool HittableObjectList::hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const {
	HitRecord temp;
	bool hit_something = false;
	double curr_closest = t_max;

	// go through objects and check if any objects are hit
	// updates t_max and hit records for current closest object hit
	for (const auto& object : objects) {
		if (object->hit(r, t_min, curr_closest, temp)) {
			hit_something = true;
			curr_closest = temp.t;
			rec = temp;
		}
	}

	return hit_something;
}
