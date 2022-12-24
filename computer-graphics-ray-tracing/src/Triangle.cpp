#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>
#include <Eigen/Dense>
using namespace std;

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	double xe = ray.origin[0];
	double ye = ray.origin[1];
	double ze = ray.origin[2];

	double xd = ray.direction[0];
	double yd = ray.direction[1];
	double zd = ray.direction[2];

	double xa = (get<0>(corners))[0];
	double ya = (get<0>(corners))[1];
	double za = (get<0>(corners))[2];

	double xb = (get<1>(corners))[0];
	double yb = (get<1>(corners))[1];
	double zb = (get<1>(corners))[2];

	double xc = (get<2>(corners))[0];
	double yc = (get<2>(corners))[1];
	double zc = (get<2>(corners))[2];

	Eigen::MatrixXf beta_numerator(3, 3);
	Eigen::MatrixXf gamma_numerator(3, 3);
	Eigen::MatrixXf t_before_numerator(3, 3);
	Eigen::MatrixXf A(3, 3);

	A << (xa - xb), (xa - xc), (xd),
		 (ya - yb), (ya - yc), (yd),
		 (za - zb), (za - zc), (zd);

	

	t_before_numerator << (xa - xb), (xa - xc), (xa - xe),
		                  (ya - yb), (ya - yc), (ya - ye),
		                  (za - zb), (za - zc), (za - ze);
	auto t_before = t_before_numerator.determinant() / A.determinant();

	if (t_before < min_t) {
		return false;
	}

	gamma_numerator << (xa - xb), (xa - xe), (xd),
		(ya - yb), (ya - ye), (yd),
		(za - zb), (za - ze), (zd);
	auto gamma = gamma_numerator.determinant() / A.determinant();

	if (gamma < 0 || gamma > 1) {
		return false;
	}

	beta_numerator << (xa - xe), (xa - xc), (xd),
		(ya - ye), (ya - yc), (yd),
		(za - ze), (za - zc), (zd);
	auto beta = beta_numerator.determinant() / A.determinant();

	if (beta < 0 || beta >(1 - gamma)) {
		return false;
	}

	auto BA = (get<1>(corners)) - (get<0>(corners));
	auto CA = (get<2>(corners)) - (get<0>(corners));

	auto normal = BA.cross(CA);
	normal.normalize();
	
	t = t_before;
	n = normal;
	return true;

  ////////////////////////////////////////////////////////////////////////////
}


