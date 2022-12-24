#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  
  // Replace with your code here:
	double dummy_t;
	Eigen::Vector3d dummy_n;
	int dummy_hit_id;
	if (first_hit(ray, min_t, triangles, dummy_hit_id, dummy_t, dummy_n)) {
		t = dummy_t;
		n = dummy_n;
		return true;
	}
	

	return false;
  ////////////////////////////////////////////////////////////////////////////
}



