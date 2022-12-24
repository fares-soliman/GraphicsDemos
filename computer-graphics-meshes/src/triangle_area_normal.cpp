#include "triangle_area_normal.h"
#include <Eigen/Geometry>

Eigen::RowVector3d triangle_area_normal(
  const Eigen::RowVector3d & a, 
  const Eigen::RowVector3d & b, 
  const Eigen::RowVector3d & c)
{
	//adapted from https://math.stackexchange.com/a/2251957
	return 0.5 * (b - a).cross(c - a);
}
