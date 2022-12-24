#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  Eigen::Vector3d & rgb)
{

  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	int hit_id;
	double t;
	Eigen::Vector3d n;
	double fudge_factor = 0.01;
	if (first_hit(ray, 0, objects, hit_id, t, n)) {
		rgb = blinn_phong_shading(ray, hit_id, t, n, objects, lights);
		if (num_recursive_calls < 1) {
			if (objects[hit_id]->material->ks[0] < 0.0) {
				return true;
			}
			Eigen::Vector3d d;
			double max_t;
			struct Ray reflected_ray;
			reflected_ray.direction = reflect(-1 * (ray.direction.normalized()), n);
			reflected_ray.origin = ((ray.origin) + (t * ray.direction)) + (n * fudge_factor);
			Eigen::Vector3d dummy_rgb;
			raycolor(reflected_ray, min_t, objects, lights, num_recursive_calls + 1, dummy_rgb);
			dummy_rgb[0] = dummy_rgb[0] * objects[hit_id]->material->km[0];
			dummy_rgb[1] = dummy_rgb[1] * objects[hit_id]->material->km[1];
			dummy_rgb[2] = dummy_rgb[2] * objects[hit_id]->material->km[2];
			rgb += dummy_rgb;
			
		}
		return true;
	}

	rgb = Eigen::Vector3d(0, 0, 0);
	return false;

  
  ////////////////////////////////////////////////////////////////////////////
}
