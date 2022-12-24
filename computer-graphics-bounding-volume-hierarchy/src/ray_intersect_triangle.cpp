#include "ray_intersect_triangle.h"
#include <Eigen/Geometry>
#include <Eigen/Dense>

bool ray_intersect_triangle(
  const Ray & ray,
  const Eigen::RowVector3d & A,
  const Eigen::RowVector3d & B,
  const Eigen::RowVector3d & C,
  const double min_t,
  const double max_t,
  double & t)
{
  ////////////////////////////////////////////////////////////////////////////
	double xe = ray.origin[0];
	double ye = ray.origin[1];
	double ze = ray.origin[2];

	double xd = ray.direction[0];
	double yd = ray.direction[1];
	double zd = ray.direction[2];

	double xa = A[0];
	double ya = A[1];
	double za = A[2];

	double xb = B[0];
	double yb = B[1];
	double zb = B[2];

	double xc = C[0];
	double yc = C[1];
	double zc = C[2];

	Eigen::MatrixXf beta_numerator(3, 3);
	Eigen::MatrixXf gamma_numerator(3, 3);
	Eigen::MatrixXf t_before_numerator(3, 3);
	Eigen::MatrixXf A_1(3, 3);

	A_1 << (xa - xb), (xa - xc), (xd),
		(ya - yb), (ya - yc), (yd),
		(za - zb), (za - zc), (zd);



	t_before_numerator << (xa - xb), (xa - xc), (xa - xe),
		(ya - yb), (ya - yc), (ya - ye),
		(za - zb), (za - zc), (za - ze);
	auto t_before = t_before_numerator.determinant() / A_1.determinant();

	if (t_before < min_t || t_before > max_t) {
		return false;
	}

	gamma_numerator << (xa - xb), (xa - xe), (xd),
		(ya - yb), (ya - ye), (yd),
		(za - zb), (za - ze), (zd);
	auto gamma = gamma_numerator.determinant() / A_1.determinant();

	if (gamma < 0 || gamma > 1) {
		return false;
	}

	beta_numerator << (xa - xe), (xa - xc), (xd),
		(ya - ye), (ya - yc), (yd),
		(za - ze), (za - zc), (zd);
	auto beta = beta_numerator.determinant() / A_1.determinant();

	if (beta < 0 || beta >(1 - gamma)) {
		return false;
	}

	t = t_before;
	return true;
  ////////////////////////////////////////////////////////////////////////////
}

