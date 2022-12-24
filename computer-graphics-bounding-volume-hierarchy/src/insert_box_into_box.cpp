#include "insert_box_into_box.h"

void insert_box_into_box(
  const BoundingBox & A,
  BoundingBox & B)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

	if (A.max_corner[0] > B.max_corner[0]) {
		B.max_corner[0] = A.max_corner[0];
	}
	if (A.max_corner[1] > B.max_corner[1]) {
		B.max_corner[1] = A.max_corner[1];
	}
	if (A.max_corner[2] > B.max_corner[2]) {
		B.max_corner[2] = A.max_corner[2];
	}

	if (A.min_corner[0] < B.min_corner[0]) {
		B.min_corner[0] = A.min_corner[0];
	}
	if (A.min_corner[1] < B.min_corner[1]) {
		B.min_corner[1] = A.min_corner[1];
	}
	if (A.min_corner[2] < B.min_corner[2]) {
		B.min_corner[2] = A.min_corner[2];
	}

}

