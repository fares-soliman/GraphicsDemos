#include "box_box_intersect.h"
bool box_box_intersect(
  const BoundingBox & A,
  const BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
	bool Xs = A.max_corner[0] >= B.min_corner[0] && B.max_corner[0] >= A.min_corner[0];
	bool Ys = A.max_corner[1] >= B.min_corner[1] && B.max_corner[1] >= A.min_corner[1];
	bool Zs = A.max_corner[2] >= B.min_corner[2] && B.max_corner[2] >= A.min_corner[2];

	return Xs && Ys && Zs;

  ////////////////////////////////////////////////////////////////////////////
}

