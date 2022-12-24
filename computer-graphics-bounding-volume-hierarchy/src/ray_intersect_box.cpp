#include "ray_intersect_box.h"
#include <iostream>
#include <algorithm>
using namespace std;

bool ray_intersect_box(
  const Ray & ray,
  const BoundingBox& box,
  const double min_t,
  const double max_t)
{
	double t_min_x, t_max_x;
	double t_min_y, t_max_y;
	double t_min_z, t_max_z;
	double a_x = 1 / ray.direction[0];
	double a_y = 1 / ray.direction[1];
	double a_z = 1 / ray.direction[2];

    if (a_x >= 0) {
        t_min_x = a_x * (box.min_corner[0] - ray.origin[0]);
        t_max_x = a_x * (box.max_corner[0] - ray.origin[0]);
    }
    else {
        t_min_x = a_x * (box.max_corner[0] - ray.origin[0]);
        t_max_x = a_x * (box.min_corner[0] - ray.origin[0]);
    }
    if (a_y >= 0) {
        t_min_y = a_y * (box.min_corner[1] - ray.origin[1]);
        t_max_y = a_y * (box.max_corner[1] - ray.origin[1]);
    }
    else {
        t_min_y = a_y * (box.max_corner[1] - ray.origin[1]);
        t_max_y = a_y * (box.min_corner[1] - ray.origin[1]);
    }
    if (a_z >= 0) {
        t_min_z = a_z * (box.min_corner[2] - ray.origin[2]);
        t_max_z = a_z * (box.max_corner[2] - ray.origin[2]);
    }
    else {
        t_min_z = a_z * (box.max_corner[2] - ray.origin[2]);
        t_max_z = a_z * (box.min_corner[2] - ray.origin[2]);
    }

    double min_max = std::min({ t_max_x, t_max_y, t_max_z });
    double max_min = std::max({ t_min_x, t_min_y, t_min_z });

    if (min_max > max_min) {
        return true;
    }
    return false;
}
