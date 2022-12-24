#include "hue_shift.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void hue_shift(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double shift,
  std::vector<unsigned char> & shifted)
{
  shifted.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  for (int i = 0; i < width * height * 3; i = i + 3) {
	  double h, s, v;
	  rgb_to_hsv((double)rgb[i], (double)rgb[i + 1], (double)rgb[i + 2], h, s, v);
	  h = h + shift;
	  if (h > 360) {
		  h = h - 360;
	  }
	  double r, g, b;
	  hsv_to_rgb(h, s, v, r, g, b);
	  shifted[i] = (int)r;
	  shifted[i+1] = (int)g;
	  shifted[i+2] = (int)b;

  }

}
