#include "catmull_rom_interpolation.h"
#include <Eigen/Dense>
#include <cmath>

using namespace std;

Eigen::Vector3d catmull_rom_interpolation(
  const std::vector<std::pair<double, Eigen::Vector3d> > & keyframes,
  double t)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code

	if (keyframes.size() == 0) {
		return Eigen::Vector3d(0, 0, 0);
	}

	if (keyframes.size() == 1) {
		return keyframes[0].second;
	}

	double actual_time = fmod(t, keyframes.back().first);
	double t1;
	double t_1;

	Eigen::Vector3d mk1;
	Eigen::Vector3d mk;
	Eigen::Vector3d pk1;
	Eigen::Vector3d pk2;
	Eigen::Vector3d pk_1;
	Eigen::Vector3d pk;

	int i;
	for (i = 1; i < keyframes.size(); ++i) {
		if (actual_time < keyframes[i].first) {
			break;
		}
	}

	t1 = keyframes[i].first;
	t_1 = keyframes[i - 1].first;
	double t_diff = (actual_time - t_1) / (t1 - t_1);
	pk1 = keyframes[i].second;
	if ((i + 1) < (keyframes.size() - 1)) {
		pk2 = keyframes[i + 1].second;
	}
	else {
		pk2 = keyframes[i].second;
	}
	pk = keyframes[i - 1].second;

	if ((i - 2) > 0) {
		pk_1 = keyframes[i - 2].second;
	}
	else {
		pk_1 = keyframes[i - 1].second;
	}


	Eigen::RowVector4d u(1, t_diff, pow(t_diff, 2), pow(t_diff, 3));

	Eigen::Matrix4d trans;

	trans << 0, 2, 0, 0,
			-1, 0, 1, 0,
			2, -5, 4, -1,
			-1, 3, -3, 1;

	Eigen::MatrixXd positions(4, 3);

	positions << pk_1(0), pk_1(1), pk_1(2),
				pk(0), pk(1), pk(2),
				pk1(0), pk1(1), pk1(2),
				pk2(0), pk2(1), pk2(2);
	

	return 0.5 * u * trans * positions;





  /*return Eigen::Vector3d(0,0,0);*/
  /////////////////////////////////////////////////////////////////////////////
}
