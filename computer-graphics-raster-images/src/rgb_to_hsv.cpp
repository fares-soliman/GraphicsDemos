#include "rgb_to_hsv.h"
#include <algorithm>
using namespace std;

void rgb_to_hsv(
  const double r,
  const double g,
  const double b,
  double & h,
  double & s,
  double & v)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  h = 0;
  s = 0;
  v = 0;

  double c = 0;

  double r_dash = r / 255;
  double g_dash = g / 255;
  double b_dash = b / 255;

  double first_max = max(r_dash, g_dash);
  double final_max = max(first_max, b_dash);

  v = final_max;

  double first_min = min(r_dash, g_dash);
  double final_min = min(first_min, b_dash);

  c = final_max - final_min;

  if (v == 0) {
	  s = 0;
  }
  else {
	  s = c / v;
  }

  double h_dash = 0;

  if (c != 0) {

	  if (final_max == r_dash) {
		  h_dash = fmod(((g_dash - b_dash) / c), 6);
	  }

	  else if (final_max == g_dash) {
		  h_dash = ((b_dash - r_dash) / c) + 2;
	  }

	  else if (final_max == b_dash) {
		  h_dash = ((r_dash - g_dash) / c) + 4;

	  }

  }

  h = h_dash * 60;

	



  ////////////////////////////////////////////////////////////////////////////
}
