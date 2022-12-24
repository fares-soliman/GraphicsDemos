#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  int offset = 0;

	for (int j = 0; j < height * width * 4; j = j + 4) {
		rgb[j -offset] = rgba[j];
		rgb[j + 1 - offset] = rgba[j+1];
		rgb[j + 2 - offset] = rgba[j + 2];
		offset++;
	}
  
}
