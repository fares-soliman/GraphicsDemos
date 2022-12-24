#include "ray_intersect_triangle_mesh_brute_force.h"
#include "ray_intersect_triangle.h"
#include <limits>

bool ray_intersect_triangle_mesh_brute_force(
  const Ray & ray,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double min_t,
  const double max_t,
  double & hit_t,
  int & hit_f)
{
  ////////////////////////////////////////////////////////////////////////////
	double min_distance = std::numeric_limits<double>::infinity();
	int f_that_hit;
	bool hit = false;

	for (int i = 0; i < F.rows(); ++i) {
		Eigen::RowVector3d A(V(F(i, 0), 0), V(F(i, 0), 1), V(F(i, 0), 2));
		Eigen::RowVector3d B(V(F(i, 1), 0), V(F(i, 1), 1), V(F(i, 1), 2));
		Eigen::RowVector3d C(V(F(i, 2), 0), V(F(i, 2), 1), V(F(i, 2), 2));

		double dummy_t;
		if (ray_intersect_triangle(ray, A, B, C, min_t, max_t, dummy_t)) {
			hit = true;
			if (dummy_t < min_distance) {
				min_distance = dummy_t;
				f_that_hit = i;
			}
		}

	}

	if (hit){
		hit_t = min_distance;
		hit_f = f_that_hit;
		return true;
	}
	
	return false;
  ////////////////////////////////////////////////////////////////////////////
}
