#include "euler_angles_to_transform.h"
#define M_PI   3.14159265358979323846264338327950288

Eigen::Affine3d euler_angles_to_transform(
  const Eigen::Vector3d & xzx)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
 
    Eigen::Affine3d first_x = Eigen::Affine3d(Eigen::AngleAxisd((xzx[0] * M_PI) / 180.0, Eigen::Vector3d(1, 0, 0)));
    Eigen::Affine3d z = Eigen::Affine3d(Eigen::AngleAxisd((xzx[1] * M_PI) / 180.0, Eigen::Vector3d(0, 0, 1)));
    Eigen::Affine3d  second_x = Eigen::Affine3d(Eigen::AngleAxisd((xzx[2] * M_PI) / 180.0, Eigen::Vector3d(1, 0, 0)));
    Eigen::Affine3d A = second_x * z * first_x;
    return A;
  /* Eigen::Affine3d A;
  A.matrix() << 
    1,0,0,0,
    0,1,0,0,
    0,0,1,0,
    0,0,0,1;
  return A;*/
  /////////////////////////////////////////////////////////////////////////////
}
