#include "simulate_bayer_mosaic.h"

void simulate_bayer_mosaic(
  const std::vector<unsigned char> & rgb,
  const int & width,
  const int & height,
  std::vector<unsigned char> & bayer)
{
  bayer.resize(width*height);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  bool GB = false;
  bool GorB = true;
  bool RorG = true;

  int bayer_iterator = 0;

  for (int h = 0; h < height; ++h) {
	  GB = !GB;
	  GorB = true;
	  RorG = true;
	  for (int w = 0; w < width; ++w) {

		  if (GB) {
			  if (GorB) {
				  bayer[bayer_iterator] = rgb[1 + 3 * (w + width * h)];
			  }
			  else {
				  bayer[bayer_iterator] = rgb[2 + 3 * (w + width * h)];
			  }
			  GorB = !GorB;
		  }

		  else {
			  if (RorG) {
				  bayer[bayer_iterator] = rgb[3 * (w + width * h)];
			  }
			  else {
				  bayer[bayer_iterator] = rgb[1 + 3 * (w + width * h)];
			  }
			  RorG = !RorG;
		  }

		  bayer_iterator++;
	  }
  }

}
