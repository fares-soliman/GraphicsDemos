#include "Sphere.h"
#include "Ray.h"
#include <cmath>
#include <Eigen/Geometry>
bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	double determinant1 = pow(ray.direction.dot(ray.origin - center), 2);
	double determinant2 = ((ray.origin - center).dot(ray.origin - center)) - pow(radius, 2);
	double determinant3 = (ray.direction.dot(ray.direction)) * determinant2;
	double determinant = determinant1 - determinant3;

	if (determinant < 0) {
		return false;
	}

	else if (determinant < 0.00001 && determinant > -0.00001) {
		t = ((ray.direction * -1).dot(ray.origin - center)) / (ray.direction.dot(ray.direction));
		if (t > 0) {
			n = ((ray.origin + (t * ray.direction)) - center) / radius;
			return true;
		}
		return false;
	}

	else {
		double denominator = ray.direction.dot(ray.direction);
		double t1_num = ((ray.direction * -1).dot(ray.origin - center)) + pow(determinant, 0.5);
		double t2_num = ((ray.direction * -1).dot(ray.origin - center)) - pow(determinant, 0.5);

		if (t1_num < t2_num) {
			if ((t1_num / denominator) > min_t) {
				t = t1_num / denominator;
				n = ((ray.origin + (t * ray.direction)) - center) / radius;
				return true;
			}
			else {
				if ((t2_num / denominator) > min_t) {
					t = t2_num / denominator;
					n = ((ray.origin + (t * ray.direction)) - center) / radius;
					return true;
				}
				return false;
			}
			
		}
		else if (t1_num > t2_num){
			if ((t2_num / denominator) > min_t) {
				t = t2_num / denominator;
				n = ((ray.origin + (t * ray.direction)) - center) / radius;
				return true;
			}
			else {
				if ((t1_num / denominator) > min_t) {
					t = t1_num / denominator;
					n = ((ray.origin + (t * ray.direction)) - center) / radius;
					return true;
				}
				return false;
			}
			
		}

	}

  ////////////////////////////////////////////////////////////////////////////
}

