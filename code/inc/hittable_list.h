#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable_object.h"
#include <memory>
#include <vector>

class hittable_list : public hittable_object {
	public:
		hittable_list() {}
		hittable_list(std::shared_ptr<hittable_object> object) { add(object); }

		void clear() { objects.clear(); }
		void add(std::shared_ptr<hittable_object> object) { objects.push_back(object); }

		virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override;

		std::vector<std::shared_ptr<hittable_object>> objects;
};

#endif 
