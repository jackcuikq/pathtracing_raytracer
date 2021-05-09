#ifndef CAMERA_H
#define CAMERA_H

#include "utility.h"
#include "ray.h"

class Camera {
	public:
		// vfov: vertical field-of-view in degrees
		Camera(Point3 lookfrom, Point3 lookat, Vec3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist) {
			double theta = degrees_to_radians(vfov);
			double h = tan(theta / 2);
			double viewport_height = 2.0 * h;
			double viewport_width = aspect_ratio * viewport_height;

			w = unit_vector(lookfrom - lookat);
			u = unit_vector(cross(vup, w));
			v = cross(w, u);

			origin = lookfrom;
			horizontal = focus_dist * viewport_width * u;
			vertical = focus_dist * viewport_height * v;
			lower_left_corner = origin - horizontal / 2 - vertical / 2 - focus_dist*w;

			lens_rad = aperture / 2;
		}

		Ray get_ray(double s, double t) const {
			Vec3 rd = lens_rad * random_in_unit_disk();
			Vec3 offset = u * rd.x() + v * rd.y();
			return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
		}

	private:
		Point3 origin;
		Point3 lower_left_corner;
		Vec3 horizontal;
		Vec3 vertical;
		Vec3 u, v, w;
		double lens_rad;
};


#endif // !CAMERA_H
