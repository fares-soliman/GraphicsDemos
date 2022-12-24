#include "triangle_triangle_intersection.h"
#include "ray_intersect_triangle.h"


bool triangle_triangle_intersection(
  const Eigen::RowVector3d & A0,
  const Eigen::RowVector3d & A1,
  const Eigen::RowVector3d & A2,
  const Eigen::RowVector3d & B0,
  const Eigen::RowVector3d & B1,
  const Eigen::RowVector3d & B2)
{
    Ray e1(A0, A1 - A0), e2(A0, A2 - A0), e3(A1, A2 - A1), e4(B0, B1 - B0), e5(B0, B2 - B0), e6(B1, B2 - B1);
    double min_t = 0.0, max_t = 1.0, t;

    if (ray_intersect_triangle(e1, B0, B1, B2, min_t, max_t, t))
        return true;
    if (ray_intersect_triangle(e2, B0, B1, B2, min_t, max_t, t))
        return true;
    if (ray_intersect_triangle(e3, B0, B1, B2, min_t, max_t, t))
        return true;
    if (ray_intersect_triangle(e4, A0, A1, A2, min_t, max_t, t))
        return true;
    if (ray_intersect_triangle(e5, A0, A1, A2, min_t, max_t, t))
        return true;
    if (ray_intersect_triangle(e6, A0, A1, A2, min_t, max_t, t))
        return true;
    return false;
}
