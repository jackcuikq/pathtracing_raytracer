#ifndef MATERIAL_H
#define MATERIAL_H

#include "hittable_object.h"

struct HitRecord;

class Material {
	public:
		virtual bool scatter(const Ray& ray_in, const HitRecord& rec, Colour& attenuation, Ray& scattered) const = 0;
};

class Lambertian : public Material {
	public:
		Lambertian(const Colour& a) : albedo(a) {}

		virtual bool scatter(const Ray& ray_in, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override {
			auto scatter_dir = rec.normal + random_unit_vector();

			// catch zero scatter direction vector when random unit vector is
			// exactly opposite of normal
			if (scatter_dir.near_zero()) {
				scatter_dir = rec.normal;
			}

			scattered = Ray(rec.p, scatter_dir);
			attenuation = albedo;
			return true;
		}

		Colour albedo;
};

class Metal : public Material {
	public:
		Metal(const Colour& a) : albedo(a) {}

		virtual bool scatter(const Ray& ray_in, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override {
			Vec3 reflected = reflect(unit_vector(ray_in.direction()), rec.normal);
			scattered = Ray(rec.p, reflected);
			attenuation = albedo;
			return (dot(scattered.direction(), rec.normal) > 0);
		}

		Colour albedo;
};

class Dielectric : public Material {
	public:
		Dielectric(double refraction_index) : ri(refraction_index) {}

		virtual bool scatter(const Ray& ray_in, const HitRecord& rec, Colour& attenuation, Ray& scattered) const override {
			attenuation = Colour(1.0, 1.0, 1.0);
			double refraction_ratio = rec.front_face ? (1.0 / ri) : ri;

			Vec3 unit_dir = unit_vector(ray_in.direction());

			// solve for sin_theta: sin(theta) = sqrt(1 - (cos(theta))^2)
			double cos_theta = fmin(dot(-unit_dir, rec.normal), 1.0);
			double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

			// from Snell's law no solution if this is true
			bool cant_refract = refraction_ratio * sin_theta > 1.0;
			Vec3 dir;

			if (cant_refract || reflectance(cos_theta, refraction_ratio) > random_double())
				// reflect ray
				dir = reflect(unit_dir, rec.normal);
			else
				dir = refract(unit_dir, rec.normal, refraction_ratio);

			scattered = Ray(rec.p, dir);
			return true;
		}

		// refraction index
		double ri;

		private:
			// use Schlick's approximation for reflectance
			static double reflectance(double cos, double ref_ind) {
				auto r0 = (1 - ref_ind) / (1 + ref_ind);
				r0 = r0 * r0;
				return r0 + (1 - r0) * pow((1 - cos), 5);
			}
};

#endif
