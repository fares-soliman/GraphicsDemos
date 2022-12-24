#include "forward_kinematics.h"
#include "euler_angles_to_transform.h"
#include <functional> // std::function
using namespace std;

Eigen::Affine3d recrusive_helper(const Skeleton& skeleton,
	std::vector<Eigen::Affine3d, Eigen::aligned_allocator<Eigen::Affine3d> >& T,
	vector<int>& play_array, int index) {

	if (index == -1) {
		return Eigen::Affine3d::Identity();
	}

	Eigen::Affine3d trans = recrusive_helper(skeleton, T, play_array, skeleton[index].parent_index) * skeleton[index].rest_T * (euler_angles_to_transform(skeleton[index].xzx)) * (skeleton[index].rest_T).inverse();
	T[index] = trans;
	play_array[index] = 1;
	return trans;
}

void forward_kinematics(
  const Skeleton & skeleton,
  std::vector<Eigen::Affine3d,Eigen::aligned_allocator<Eigen::Affine3d> > & T)
{
	T.resize(skeleton.size(), Eigen::Affine3d::Identity());
	vector<int> play_array;
	play_array.resize(skeleton.size(), 0);

	for (int t = 0; t < play_array.size(); ++t) {
		if (play_array[t] == 0) {
			recrusive_helper(skeleton, T, play_array, t) ;
		}
	}
  /////////////////////////////////////////////////////////////////////////////


  //T.resize(skeleton.size(),Eigen::Affine3d::Identity());
  /////////////////////////////////////////////////////////////////////////////
}

