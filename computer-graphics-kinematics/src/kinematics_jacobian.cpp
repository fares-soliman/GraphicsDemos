#include "kinematics_jacobian.h"
#include "transformed_tips.h"
#include <iostream>

void kinematics_jacobian(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  Eigen::MatrixXd & J)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
	J = Eigen::MatrixXd::Zero(b.size() * 3, skeleton.size() * 3);
	Skeleton copy = skeleton;

	Eigen::VectorXd trans_tips = transformed_tips(skeleton, b);

	double h = 1e-7;

	for (int i = 0; i < b.size(); ++i) {
		auto x = trans_tips.segment(3 * i, 3);
		Eigen::VectorXi b_selected(1);
		b_selected << b[i];
		for (int j = 0; j < skeleton.size(); ++j) {
			copy[j].xzx[0] = skeleton[j].xzx[0] + h;
			Eigen::VectorXd shifted_tips_first_x = transformed_tips(copy, b_selected);
			copy[j].xzx[0] = skeleton[j].xzx[0];

			copy[j].xzx[1] = skeleton[j].xzx[1] + h;
			Eigen::VectorXd shifted_tips_z = transformed_tips(copy, b_selected);
			copy[j].xzx[1] = skeleton[j].xzx[1];

			copy[j].xzx[2] = skeleton[j].xzx[2] + h;
			Eigen::VectorXd shifted_tips_second_x = transformed_tips(copy, b_selected);
			copy[j].xzx[2] = skeleton[j].xzx[2];

			J(3 * i, 3 * j) = (shifted_tips_first_x[0] - x[0]) / h;
			J(3 * i, (3 * j) + 1) = (shifted_tips_z[0] - x[0]) / h;
			J(3 * i, (3 * j) + 2) = (shifted_tips_second_x[0]- x[0]) / h;

			J((3 * i) + 1, 3 * j) = (shifted_tips_first_x[1] - x[1]) / h;
			J((3 * i) + 1, (3 * j) + 1) = (shifted_tips_z[1] - x[1]) / h;
			J((3 * i) + 1, (3 * j) + 2) = (shifted_tips_second_x[1] - x[1]) / h;

			J((3 * i) + 2, 3 * j) = (shifted_tips_first_x[2] - x[2]) / h;
			J((3 * i) + 2, (3 * j) + 1) = (shifted_tips_z[2] - x[2]) / h;
			J((3 * i) + 2, (3 * j) + 2) = (shifted_tips_second_x[2] - x[2]) / h;
		}
	}
	//Eigen::MatrixXd
  

  
  /////////////////////////////////////////////////////////////////////////////
}
