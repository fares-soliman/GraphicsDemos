#include "Plane.h"
#include "Ray.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	double denominator = (ray.direction.dot(normal));

	if (denominator > 0.00001 || denominator < 0.00001) {
		double numerator = (point - ray.origin).dot(normal);
		double dummy_t = numerator / denominator;
		if (dummy_t > 0) {
			t = numerator / denominator;
			n = normal;
			return true;
		}
	}
	
	return false;
	
  ////////////////////////////////////////////////////////////////////////////
}

