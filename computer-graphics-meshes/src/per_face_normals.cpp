#include "per_face_normals.h"
#include "triangle_area_normal.h"
#include <iostream>
#include <Eigen/Geometry>

void per_face_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  Eigen::MatrixXd & N)
{
    N.resize(F.rows(), 3);

    for (int i = 0; i < V.rows(); ++i) {
        int vert1 = F(i, 0);
        int vert2 = F(i, 1);
        int vert3 = F(i, 2);

        Eigen::RowVector3d a = V.row(vert2) - V.row(vert1);
        Eigen::RowVector3d b = V.row(vert3) - V.row(vert1);

        auto normal_dir = a.cross(b);
        N.row(i) << normal_dir.normalized();

    }

}
