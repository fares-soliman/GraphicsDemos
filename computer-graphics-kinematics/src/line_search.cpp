#include "line_search.h"
#include <iostream>

double line_search(
  const std::function<double(const Eigen::VectorXd &)> & f,
  const std::function<void(Eigen::VectorXd &)> & proj_z,
  const Eigen::VectorXd & z,
  const Eigen::VectorXd & dz,
  const double max_step)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

	double sigma = max_step;

	for (int i = 0; i < 100000; ++i) {
		double no_dx = f(z);
		Eigen::VectorXd sum = z - (sigma * dz);
		proj_z(sum);
		double has_dx = f(sum);

		if (has_dx < no_dx) {
			return sigma;
		}

		sigma = sigma / 2;

		if (sigma == 0) {
			break;
		}

	}

	return sigma;

	
  /////////////////////////////////////////////////////////////////////////////
}
