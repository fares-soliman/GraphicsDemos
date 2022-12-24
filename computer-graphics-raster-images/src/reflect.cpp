#include "reflect.h"

void reflect(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & reflected)
{
  reflected.resize(width*height*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////
  int reflected_index = 0;

  for (int i = 0; i < height; ++i) {
	  for (int j = (width * 3)-3; j >= 0; j = j - 3) {
		  reflected[reflected_index] = input[j + (i*width*3)];
		  reflected[reflected_index + 1] = input[j + 1 + (i * width * 3)];
		  reflected[reflected_index + 2] = input[j + 2 + (i * width * 3)];
		  reflected_index = reflected_index + 3;
	  }
  }

}
