#include "desaturate.h"
#include "hsv_to_rgb.h"
#include "rgb_to_hsv.h"

void desaturate(
  const std::vector<unsigned char> & rgb,
  const int width,
  const int height,
  const double factor,
  std::vector<unsigned char> & desaturated)
{
  desaturated.resize(rgb.size());
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  for (int i = 0; i < width * height * 3; i = i + 3) {
	  double h, s, v;
	  rgb_to_hsv((double)rgb[i], (double)rgb[i + 1], (double)rgb[i + 2], h, s, v);
	  s = s * (1-factor);
	  double r, g, b;
	  hsv_to_rgb(h, s, v, r, g, b);
	  desaturated[i] = (int)r;
	  desaturated[i + 1] = (int)g;
	  desaturated[i + 2] = (int)b;

  }
}
