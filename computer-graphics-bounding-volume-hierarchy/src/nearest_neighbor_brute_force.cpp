#include "nearest_neighbor_brute_force.h"
#include <limits>// std::numeric_limits<double>::infinity();
#include <math.h>

void nearest_neighbor_brute_force(
  const Eigen::MatrixXd & points,
  const Eigen::RowVector3d & query,
  int & I,
  double & sqrD)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:

	int internalI = -1;
	sqrD = std::numeric_limits<double>::infinity();

	Eigen::RowVector3d the_point;
  
	for (int i = 0; i < points.rows(); ++i) {
		double distance_x = pow(points(i, 0) - query[0], 2);
		double distance_y = pow(points(i, 1) - query[1], 2);
		double distance_z = pow(points(i, 2) - query[2], 2);
		double euclid_distance = distance_x + distance_y + distance_z;

		if (euclid_distance < sqrD) {
			sqrD = euclid_distance;
			I = i;
		}
	}
  ////////////////////////////////////////////////////////////////////////////
}
