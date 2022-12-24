#include "PointLight.h"
#include <iostream>
#include <Eigen/Dense>
using namespace std;

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////

	
	Eigen::Vector3d distance = p - q;
	//cout << distance;
	Eigen::Vector3d distance_norm = distance.normalized();
	double t = distance[0] / distance_norm[0];
	double t2 = distance[1] / distance_norm[1];
	double t3 = distance[2] / distance_norm[2];

	max_t = distance.norm(); 
	d = distance_norm;

}
