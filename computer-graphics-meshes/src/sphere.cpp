#include "sphere.h"
#include <iostream>
#include <math.h>
#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif


void sphere(
  const int num_u,
  const int num_v,
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  
    // Resize Matrices
    int faces_row = 0;
    int total_vert = (num_v - 1) * num_u + 2;
    int total_faces = num_u * num_v;

    V.resize(total_vert, 3);
    F.resize(total_faces, 4);

    UV.resize(total_vert + num_v - 1, 2);
    UF.resize(total_faces, 4);

    NV.resize(total_vert, 3);
    NF.resize(total_faces, 4);

    double step_u = 1.0 / num_u;
    double step_v = 1.0 / num_v;
    double lat_step = M_PI * step_v;
    double long_step = 2.0 * M_PI * step_u;

    double rad = 1.0;
    int v_row = 0, uv_row = 0;

    V.row(v_row) << 0, 0, -rad;
    UV.row(uv_row) << 0.5, 0;
    v_row++;
    uv_row++;

    for (int v = 1; v < num_v; ++v) {
        double lat = v * lat_step;
        double v_in_uv_coords = v * step_v;
        for (int u = 0; u < num_u; ++u) {
            double lon = u * long_step;
            double x = rad * sin(lat) * cos(lon);
            double y = rad * sin(lat) * sin(lon);
            double z = -rad * cos(lat);   
            double u_in_uv_coords = u * step_u;
            V.row(v_row++) << x, y, z;
            UV.row(uv_row++) << u_in_uv_coords, v_in_uv_coords;
        }
        UV.row(uv_row++) << 1.0, v_in_uv_coords;
    }

    V.row(v_row) << 0, 0, rad;
    UV.row(uv_row) << 0.5, 1.0;

    for (int v = 0; v < num_v; ++v) {
        for (int u = 0; u < num_u; ++u) {
            int vert1 = 0;
            int vert2 = 0;
            int vert3 = 0;
            int vert4 = 0;
            bool north_pole;
            bool south_pole;
            bool rotate;

            int start_point_old = (num_u * (v - 1)) + u + 1;
            int start_point = (num_u * v) + u + 1;

            if (v == num_v - 1) {
                north_pole = true;
            }
            else {
                north_pole = false;
            }

            if (v == 0) {
                south_pole = true;
            }
            else {
                south_pole = false;
            }

            if (u == num_u - 1) {
                rotate = true;
            }
            else {
                rotate = false;
            }

            if (south_pole) {
                vert1 = 1;
                vert4 = 1;
            }
            else {
                vert1 = start_point_old + 1;
                vert4 = start_point_old + 2;
                if (rotate)
                    vert4 -= u;
            }

            if (north_pole) {
                vert2 = v_row;
                vert3 = v_row;
            }
            else {
                vert2 = start_point + 1;
                vert3 = start_point + 2;
                if (rotate)
                    vert3 -= u;
            }

            F.row(faces_row) << vert1, vert2, vert3, vert4;

            start_point_old =  ((num_u+1) * (v - 1)) + u + 1;
            start_point =  ((num_u+1) * v) + u + 1;
            int uv1 = 0, uv2 = 0, uv3 = 0, uv4 = 0;
            if (south_pole) {
                uv1 = 1;
                uv4 = 1;
            }
            else {
                uv1 = start_point_old + 1;
                uv4 = start_point_old + 2;
            }

            if (north_pole) {
                uv2 = uv_row;
                uv3 = uv_row;
            }
            else {
                uv2 = start_point + 1;
                uv3 = start_point + 2;
            }

            UF.row(faces_row++) << uv1, uv2, uv3, uv4;
        }
    }

    for (int i = 0; i < V.rows(); ++i) {
        NV.row(i) = V.row(i).normalized();
    }
    
    NF = F;


}
