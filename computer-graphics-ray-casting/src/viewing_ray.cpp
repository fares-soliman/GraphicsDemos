#include "viewing_ray.h"
#include <Eigen/Core>
#include <Eigen/Geometry>

#define NX 640.0
#define NY 360.0

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

	double u = (camera.width / NX) * (j + 0.5) - (camera.width / 2);
	double v = ((camera.height / NY) * (i + 0.5) - (camera.height / 2)) * -1;

	ray.origin = camera.e;

	Eigen::Vector3d row1 = Eigen::Vector3d(camera.u[0], camera.v[0], camera.w[0]);
	Eigen::Vector3d row2 = Eigen::Vector3d(camera.u[1], camera.v[1], camera.w[1]);
	Eigen::Vector3d row3 = Eigen::Vector3d(camera.u[2], camera.v[2], camera.w[2]);

	Eigen::Vector3d vector;

	vector << u, v, camera.d * -1;

	double first_element = row1.dot(vector);
	double second_element = row2.dot(vector);
	double third_element = row3.dot(vector);

	ray.direction = Eigen::Vector3d(first_element, second_element, third_element);

}

