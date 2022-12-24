#include "per_corner_normals.h"
#include "triangle_area_normal.h"
// Hint:
#include "vertex_triangle_adjacency.h"
#include "per_face_normals.h"
#include <iostream>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void per_corner_normals(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const double corner_threshold,
  Eigen::MatrixXd & N)
{
    std::vector< std::vector<int> > VF;
    Eigen::MatrixXd FN;
    N.resize(F.rows() * 3, 3);

    vertex_triangle_adjacency(F, V.rows(), VF);
    per_face_normals(V, F, FN);

    double threshold = cos(corner_threshold * M_PI / 180.0);

    for (int i = 0; i < F.rows(); ++i) {
        auto f_norm = FN.row(i);
        for (int j = 0; j < F.cols(); ++j) {
            int vertex = F(i, j);
            std::vector<int> adjacent_faces = VF[vertex];
            Eigen::RowVector3d n = Eigen::RowVector3d(0, 0, 0);

            for (int adjacent_face : adjacent_faces) {
                if (FN.row(adjacent_face).dot(f_norm) > threshold) {
                    n = n + triangle_area_normal(V.row(F(adjacent_face, 0)), V.row(F(adjacent_face, 1)), V.row(F(adjacent_face, 2)));
                }
            }
            N.row((3 * i) + j) << n.normalized();
        }
    }
}
