#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <limits>
#include <cmath>
#include <vector>

using namespace std;

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	Eigen::Vector3d ambient = Eigen::Vector3d((objects[hit_id]->material->ka[0]) * (0.1),
		(objects[hit_id]->material->ka[1]) * (0.1),
		(objects[hit_id]->material->ka[2]) * (0.1));

	Eigen::Vector3d lambertian = Eigen::Vector3d(0, 0, 0);
	Eigen::Vector3d reflection = Eigen::Vector3d(0, 0, 0);
	double fudge_factor = 0.01;

	for (int i = 0; i < lights.size(); ++i) {
		Eigen::Vector3d d;
		double max_t;
		lights[i]->direction((ray.origin + (t * ray.direction)), d, max_t);

		Eigen::Vector3d point_on_shape = (ray.origin + (t * ray.direction));

		Eigen::Vector3d fudged = ((ray.origin) + (t * ray.direction)) + (n * fudge_factor);

		bool hit = false;
		struct Ray d_ray;
		d_ray.direction = d;
		d_ray.origin = ((ray.origin) + (t * ray.direction)) + (n * fudge_factor);
		double dummy_t;
		int dummy_hit_id;
		Eigen::Vector3d dummy_n;

		if (first_hit(d_ray, 0, objects, dummy_hit_id, dummy_t, dummy_n)) {
			if (dummy_t < max_t)
				hit = true;
		}
		
		if (!hit) {
			double lambertian_1 = (objects[hit_id]->material->kd[0]) * ((lights[i]->I[0])) * (max(0.0, n.dot(d)));
			double lambertian_2 = (objects[hit_id]->material->kd[1]) * ((lights[i]->I[1])) * (max(0.0, n.dot(d)));
			double lambertian_3 = (objects[hit_id]->material->kd[2]) * ((lights[i]->I[2])) * (max(0.0, n.dot(d)));
			lambertian += Eigen::Vector3d(lambertian_1, lambertian_2, lambertian_3);

			Eigen::Vector3d v = -1 * (ray.direction.normalized());
			Eigen::Vector3d h = (v + d) / ((v + d).norm());

			double reflection_1 = (objects[hit_id]->material->ks[0]) * ((lights[i]->I[0])) * pow((max(0.0, n.dot(h))), (objects[hit_id]->material->phong_exponent));
			double reflection_2 = (objects[hit_id]->material->ks[1]) * ((lights[i]->I[1])) * pow((max(0.0, n.dot(h))), (objects[hit_id]->material->phong_exponent));
			double reflection_3 = (objects[hit_id]->material->ks[2]) * ((lights[i]->I[2])) * pow((max(0.0, n.dot(h))), (objects[hit_id]->material->phong_exponent));
			reflection += Eigen::Vector3d(reflection_1, reflection_2, reflection_3);
		}
	}

	return ambient + lambertian + reflection;
  ////////////////////////////////////////////////////////////////////////////
}
