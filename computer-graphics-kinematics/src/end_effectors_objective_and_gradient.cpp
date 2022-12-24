#include "end_effectors_objective_and_gradient.h"
#include "transformed_tips.h"
#include "kinematics_jacobian.h"
#include "copy_skeleton_at.h"
#include <iostream>
#include <cmath>

void end_effectors_objective_and_gradient(
  const Skeleton & skeleton,
  const Eigen::VectorXi & b,
  const Eigen::VectorXd & xb0,
  std::function<double(const Eigen::VectorXd &)> & f,
  std::function<Eigen::VectorXd(const Eigen::VectorXd &)> & grad_f,
  std::function<void(Eigen::VectorXd &)> & proj_z)
{
  /////////////////////////////////////////////////////////////////////////////
  // Replace with your code
  f = [&](const Eigen::VectorXd & A)->double
  {
      Skeleton trans_skeleton = copy_skeleton_at(skeleton, A);
      Eigen::VectorXd xb = transformed_tips(trans_skeleton, b);

      double Ex = 0.0;
      for (int i = 0; i < b.size(); ++i) {
          double first = pow(xb(i * 3) - xb0(i * 3), 2);
          double second = pow(xb((i * 3) + 1) - xb0((i * 3) + 1), 2);
          double third = pow(xb((i * 3) + 2) - xb0((i * 3) + 2), 2);

          Ex +=first + second + third;
      }

      return Ex;
  };
  grad_f = [&](const Eigen::VectorXd & A)->Eigen::VectorXd
  {
      Skeleton trans_skeleton = copy_skeleton_at(skeleton, A);
      Eigen::VectorXd xb = transformed_tips(trans_skeleton, b);

      Eigen::VectorXd dE_dx(3 * b.rows());

      for (int i = 0; i < b.size(); ++i) {
          dE_dx(i*3) = 2 * (xb(i * 3) - xb0(i * 3));
          dE_dx(i*3+1) = 2 * (xb((i * 3) + 1) - xb0((i * 3) + 1));
          dE_dx(i*3+2) = 2 * (xb((i * 3) + 2) - xb0((i * 3) + 2));
      }

      Eigen::MatrixXd J;
      kinematics_jacobian(trans_skeleton, b, J);

      return J.transpose() * dE_dx;
  };
  proj_z = [&](Eigen::VectorXd & A)
  {
    assert(skeleton.size()*3 == A.size());
    
    for (int i = 0; i < skeleton.size(); ++i) {
        for (int j = 0; j < 3; ++j) {
            double capped_num = 0.0;
            if (A[3 * i + j] > skeleton[i].xzx_max[j]) {
                capped_num = skeleton[i].xzx_max[j];
            }
            else {
                if (A[3 * i + j] < skeleton[i].xzx_min[j]) {
                    capped_num = skeleton[i].xzx_min[j];
                }
                else {
                    continue;
                }
            }
           

            A[i * 3 + j] = capped_num;
        }
    }

  };
  /////////////////////////////////////////////////////////////////////////////
}
