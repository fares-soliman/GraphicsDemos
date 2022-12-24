#include "linear_blend_skinning.h"

void linear_blend_skinning(
  const Eigen::MatrixXd & V,
  const Skeleton & skeleton,
  const std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T,
  const Eigen::MatrixXd & W,
  Eigen::MatrixXd & U)
{

	for (int i = 0; i < V.rows(); ++i) {
		Eigen::Vector4d VI(0, 0, 0, 0);

		for (int j = 0; j < skeleton.size(); ++j) {
			if (skeleton[j].weight_index == -1) {
				continue;
			}
			else {
				auto weight = W(i, skeleton[j].weight_index);
				VI += weight * (T[j] * Eigen::Vector4d(V.row(i)[0], V.row(i)[1], V.row(i)[2], 1));
			}
		}
		U.row(i) << VI[0] / VI[3], VI[1] / VI[3], VI[2] / VI[3];
	}

}
