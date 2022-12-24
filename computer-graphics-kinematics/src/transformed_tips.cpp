#include "transformed_tips.h"
#include "forward_kinematics.h"

Eigen::VectorXd transformed_tips(
  const Skeleton & skeleton, 
  const Eigen::VectorXi & b)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
	std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d> > T;

	forward_kinematics(skeleton, T);
	Eigen::VectorXd asnwer = Eigen::VectorXd::Zero(3 * b.size());

	for (int i = 0; i < b.size(); ++i) {
		auto transformed = T[b[i]] * skeleton[b[i]].rest_T * Eigen::Vector4d(skeleton[b[i]].length, 0, 0, 1);
		asnwer[i * 3] = transformed[0];
		asnwer[(i * 3) + 1] = transformed[1];
		asnwer[(i * 3) + 2] = transformed[2];
	}

  return asnwer;
  /////////////////////////////////////////////////////////////////////////////
}
