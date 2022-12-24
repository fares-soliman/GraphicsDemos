#include "first_hit.h"

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  
	double t_lowest = INT_MAX;
	Eigen::Vector3d n_lowest;
	int index_lowest;
	bool hit = false;

	for (int i = 0; i < objects.size(); ++i) {
		double dummy_t;
		Eigen::Vector3d dummy_n;
		if (objects[i]->intersect(ray, min_t, dummy_t, dummy_n)) {
			if (dummy_t < t_lowest) {
				hit = true;
				t_lowest = dummy_t;
				n_lowest = dummy_n;
				index_lowest = i;
			}
		}
	}

	if (hit) {
		t = t_lowest;
		n = n_lowest;
		hit_id = index_lowest;
		return true;
	}

	return false;


  ////////////////////////////////////////////////////////////////////////////
}

