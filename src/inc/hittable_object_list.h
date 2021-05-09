#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable_object.h"
#include <memory>
#include <vector>

class HittableObjectList : public HittableObject {
	public:
		HittableObjectList() {}
		HittableObjectList(std::shared_ptr<HittableObject> object) { add(object); }

		void clear() { objects.clear(); }
		void add(std::shared_ptr<HittableObject> object) { objects.push_back(object); }

		virtual bool hit(const Ray& r, double t_min, double t_max, HitRecord& rec) const override;

		std::vector<std::shared_ptr<HittableObject>> objects;
};

#endif 
