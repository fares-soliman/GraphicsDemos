#include "over.h"

void over(
  const std::vector<unsigned char> & A,
  const std::vector<unsigned char> & B,
  const int & width,
  const int & height,
  std::vector<unsigned char> & C)
{
  C.resize(A.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  /*R = R1 A1 (1 - A2) + R2 A2
	G = G1 A1 (1 - A2) + G2 A2
	B = B1 A1 (1 - A2) + B2 A2
	A = A1 (1 - A2) + A2

	1 is background / 	B is background
	2 is foreground / 	A is foreground

	*/

  for (int i = 0; i < width * height * 4; i = i + 4) {

	  double R1 = (double)B[i] / 255;
	  double G1 = (double)B[i + 1] / 255;
	  double B1 = (double)B[i + 2] / 255;

	  double R2 = (double)A[i] / 255;
	  double G2 = (double)A[i + 1] / 255;
	  double B2 = (double)A[i + 2] / 255;

	  double A1 = (double)B[i + 3] / 255;
	  double A2 = (double)A[i + 3] / 255;

	  double R1A1 = R1 * A1;
	  double G1A1 = G1 * A1;
	  double B1A1 = B1 * A1;

	  double R2A2 = R2 * A2;
	  double G2A2 = G2 * A2;
	  double B2A2 = B2 * A2;


	  double new_r = (R1A1 * (1 - A2) + R2A2) * 255;
	  double new_g = (G1A1 * (1 - A2) + G2A2) * 255;
	  double new_b = (B1A1 * (1 - A2) + B2A2) * 255;
	  double new_a = (A1 * (1 - A2) + A2) * 255;

	  C[i] = (int)new_r;
	  C[i + 1] = (int)new_g;
	  C[i + 2] = (int)new_b;
	  C[i + 3] = (int)new_a;
  }

}
