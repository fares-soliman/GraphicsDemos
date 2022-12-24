#include "hsv_to_rgb.h"
#include <stdlib.h>
#include <cmath>
using namespace std;

double dmod(double x, double y) {
	return x - (int)(x / y) * y;
}

void hsv_to_rgb(
  const double h,
  const double s,
  const double v,
  double & r,
  double & g,
  double & b)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  r = 0;
  g = 0;
  b = 0;
  ////////////////////////////////////////////////////////////////////////////

  double c = v * s;

  double modulo_result = fmod((h / 60), 2);

  double modulo_and_minus_1 = modulo_result - 1;

  if (modulo_and_minus_1 < 0.0) {
	  modulo_and_minus_1 = modulo_and_minus_1 * -1;
  }

  double x = c * (1 - modulo_and_minus_1);

  double m = v - c;

  double r_dash = 0, g_dash = 0, b_dash = 0;

  if (h >= 0 && h < 60) {
	  r_dash = c;
	  g_dash = x;
  }

  else if (h >= 60 && h < 120) {
	  r_dash = x;
	  g_dash = c;
  }

  else if (h >= 120 && h < 180) {
	  g_dash = c;
	  b_dash = x;
  }

  else if (h >= 180 && h < 240) {
	  g_dash = x;
	  b_dash = c;
  }

  else if (h >= 240 && h < 300) {
	  r_dash = x;
	  b_dash = c;
  }

  else if (h >= 300 && h < 360) {
	  r_dash = c;
	  b_dash = x;
  }

  r = (r_dash + m) * 255;
  g = (g_dash + m) * 255;
  b = (b_dash + m) * 255;

}
