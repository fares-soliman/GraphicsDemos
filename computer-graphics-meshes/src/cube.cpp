#include "cube.h"
#include <iostream>
#include <Eigen/Dense>

void cube(
  Eigen::MatrixXd & V,
  Eigen::MatrixXi & F,
  Eigen::MatrixXd & UV,
  Eigen::MatrixXi & UF,
  Eigen::MatrixXd & NV,
  Eigen::MatrixXi & NF)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here:
  ////////////////////////////////////////////////////////////////////////////

  //Hint:
   V.resize(8,3);
   F.resize(6,4);
   UV.resize(14,2);
   UF.resize(6,4);
   NV.resize(6,3);
   NF.resize(6,4);

   V << 0, 0, 0,
		1, 0, 0,
		1, 0, 1,
		0, 0, 1,
		0, 1, 0,
		0, 1, 1,
		1, 1, 1,
		1, 1, 0;
		
   F << 8, 7, 3, 2,
	   1, 4, 6, 5,
	   5, 6, 7, 8,
	   1, 2, 3, 4,
	   7, 6, 4, 3,
	   8, 2, 1, 5;

   UV << 1, 1,
		0.0, 1,
		0.0, 2,
		1, 2,
		1, 3,
		2, 3,
		2, 2,
		3, 2,
		4, 2,
		4, 1,
		3, 1,
		2, 1,
		2, 0.0,
		1, 0;

   UV /= 4.0;

   UF << 8, 7, 12, 11,
		2, 1, 4, 3,
		5, 4, 7, 6,
		14, 13, 12, 1,
		7, 4, 1, 12,
		8, 11, 10, 9;

   NV << 1, 0, 0,
		-1, 0, 0,
		0, 1, 0,
		0, -1, 0,
		0, 0, 1,
		0, 0, -1;

   NF << 1, 1, 1, 1,
		2, 2, 2, 2,
		3, 3, 3, 3,
		4, 4, 4, 4,
		5, 5, 5, 5,
		6, 6, 6, 6;

}
