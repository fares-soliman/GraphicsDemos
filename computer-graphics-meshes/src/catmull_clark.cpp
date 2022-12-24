#include "catmull_clark.h"
#include "vertex_triangle_adjacency.h"
#include <unordered_map>
#include <utility>
#include <functional>
#include <unordered_set>

void catmull_clark(
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const int num_iters,
  Eigen::MatrixXd & SV,
  Eigen::MatrixXi & SF)
{
    ///*
    // * Reference:
    // * https://en.wikipedia.org/wiki/Catmull%E2%80%93Clark_subdivision_surface
    // */
    //if (num_iters == 0)
    //    return;
    //
    //// For each face, add a face point
    //std::vector<Eigen::RowVector3d> face_points;
    //int sv_row = 0;
    //for (int i = 0; i < F.rows(); ++i) {
    //    auto avg = Eigen::RowVector3d(0.0, 0.0, 0.0);
    //    for (int j = 0; j < F.cols(); ++j)
    //        avg += V.row(F(i, j));
    //    avg /= (double)F.cols();
    //    face_points.push_back(avg);
    //    SV.row(sv_row++) << avg;
    //}

    //// Get all edges in mesh
    //for (int i = 0; i < F.rows(); ++i) {
    //    for (int j = 0; j < F.cols(); ++j) {
    //        int v0 = F(i, (j + 3) % 4);
    //        int v1 = F(i, j);
    //        int v2 = F(i, (j + 1) % 4);
    //        auto forward_edge = std::make_pair(v1, v2);
    //        auto backward_edge = std::make_pair(v2, v1);

    //        VV[v1].insert(v0);
    //        VV[v1].insert(v2);

    //        bool exists = false;
    //        for (int k = 0; k < E.size(); ++k) {
    //            if (E[k] == forward_edge || E[k] == backward_edge) {
    //                exists = true;
    //                FE[k] = std::make_pair(FE[k].first, i);
    //                break;
    //            }
    //        }

    //        if (!exists) {
    //            E.push_back(forward_edge);
    //            FE.push_back(std::make_pair(i, -1));
    //        }
    //    }
    //}

    //for (int i = 0; i < E.size(); ++i) {
    //    Eigen::RowVector3d avg = Eigen::RowVector3d(0.0, 0.0, 0.0);
    //    avg += V.row(E[i].first) + V.row(E[i].second);
    //    avg += face_points[FE[i].first] + face_points[FE[i].second];
    //    avg /= 4.0;
    //    edge_points.push_back(avg);
    //    SV.row(sv_row++) << avg;
    //}



    //    // Necessary data structures
    //std::vector<std::pair<int, int>> E;     	// All edges
    //std::vector<std::pair<int, int>> FE;    	// Faces neighbouring edge
    //std::vector<std::vector<int>> VF;       	// Faces neighbouring vertex
    //std::vector<std::unordered_set<int>> VV;      // Vertices neighbouring vertex

    //vertex_triangle_adjacency(F, V.rows(), VF);
    //VV.resize(V.rows());

    //std::vector<Eigen::RowVector3d> face_points;
    //std::vector<Eigen::RowVector3d> edge_points;

    //// Get all edges in mesh
    //for (int i = 0; i < F.rows(); ++i) {
    //    for (int j = 0; j < F.cols(); ++j) {
    //        int v0 = F(i, (j + 3) % 4);
    //        int v1 = F(i, j);
    //        int v2 = F(i, (j + 1) % 4);
    //        auto forward_edge = std::make_pair(v1, v2);
    //        auto backward_edge = std::make_pair(v2, v1);

    //        VV[v1].insert(v0);
    //        VV[v1].insert(v2);

    //        bool exists = false;
    //        for (int k = 0; k < E.size(); ++k) {
    //            if (E[k] == forward_edge || E[k] == backward_edge) {
    //                exists = true;
    //                FE[k] = std::make_pair(FE[k].first, i);
    //                break;
    //            }
    //        }

    //        if (!exists) {
    //            E.push_back(forward_edge);
    //            FE.push_back(std::make_pair(i, -1));
    //        }
    //    }
    //}

    //// Resize outputs to get ready to accept data
    //SV.resize(V.rows() + F.rows() + E.size(), 3);
    //SF.resize(F.rows() * F.cols(), 4);
    //int sv_row = 0, sf_row = 0;

    //// For each face, add a face point
    //int face_point_offset = sv_row;
    //for (int i = 0; i < F.rows(); ++i) {
    //    auto avg = Eigen::RowVector3d(0.0, 0.0, 0.0);
    //    for (int j = 0; j < F.cols(); ++j)
    //        avg += V.row(F(i, j));
    //    avg /= (double)F.cols();
    //    face_points.push_back(avg);
    //    SV.row(sv_row++) << avg;
    //}

    //// For each edge, add an edge point
    //int edge_point_offset = sv_row;
    //for (int i = 0; i < E.size(); ++i) {
    //    Eigen::RowVector3d avg = Eigen::RowVector3d(0.0, 0.0, 0.0);
    //    avg += V.row(E[i].first) + V.row(E[i].second);
    //    avg += face_points[FE[i].first] + face_points[FE[i].second];
    //    avg /= 4.0;
    //    edge_points.push_back(avg);
    //    SV.row(sv_row++) << avg;
    //}

    //// For each original point P, take the average F 
    //// of all n (recently created) face points for faces 
    //// touching P, and take the average R of all n edge 
    //// midpoints for (original) edges touching P, where 
    //// each edge midpoint is the average of its two endpoint 
    //// vertices (not to be confused with new "edge points" above). 
    //// Move each original point to the barycenter
    //int vertex_offset = sv_row;
    //for (int i = 0; i < V.rows(); ++i) {
    //    auto adj_faces = VF[i];
    //    auto f = Eigen::RowVector3d(0.0, 0.0, 0.0);
    //    auto r = Eigen::RowVector3d(0.0, 0.0, 0.0);
    //    auto p = V.row(i);
    //    int n = adj_faces.size();
    //    for (int face : adj_faces)
    //        f += face_points[face];
    //    f /= (double)n;

    //    for (int v : VV[i]) {
    //        auto midpoint = (V.row(v) + p) / 2.0;
    //        r += midpoint;
    //    }
    //    r /= VV[i].size();

    //    // Barycenter
    //    auto barycenter = (f + 2.0 * r + ((double)n - 3.0) * p) / (double)n;
    //    SV.row(sv_row++) << barycenter;
    //}

    //// Define new faces as enclosed by edges
    //for (int i = 0; i < F.rows(); ++i) {
    //    int v1, v2, v3, v4;
    //    v3 = face_point_offset + i;
    //    for (int j = 0; j < F.cols(); ++j) {
    //        v1 = vertex_offset + F(i, j);
    //        auto e1_fw = std::make_pair(F(i, j), F(i, (j + 1) % F.cols()));
    //        auto e1_bw = std::make_pair(e1_fw.second, e1_fw.first);

    //        auto e2_fw = std::make_pair(F(i, j), F(i, (j + 3) % 4));
    //        auto e2_bw = std::make_pair(e2_fw.second, e2_fw.first);

    //        for (int k = 0; k < E.size(); ++k) {
    //            if (E[k] == e1_fw || E[k] == e1_bw)
    //                v2 = k;
    //            if (E[k] == e2_fw || E[k] == e2_bw)
    //                v4 = k;
    //        }

    //        v2 += edge_point_offset;
    //        v4 += edge_point_offset;

    //        SF.row(sf_row++) << v1, v2, v3, v4;
    //    }
    //}

    //// Recursive call
    //Eigen::MatrixXd new_SV;
    //Eigen::MatrixXi new_SF;
    //catmull_clark(SV, SF, num_iters - 1, new_SV, new_SF);
    //if (num_iters > 1) {
    //    SV = new_SV;
    //    SF = new_SF;
    //}
}
