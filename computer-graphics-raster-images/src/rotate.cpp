#include "rotate.h"

void rotate(
  const std::vector<unsigned char> & input,
  const int width,
  const int height,
  const int num_channels,
  std::vector<unsigned char> & rotated)
{
  rotated.resize(height*width*num_channels);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  //int rotated_index = 0;

  int master_width = width;
  int master_height = height;
  int rotated_index = 0;

  for (int i = (width * 3) - 3; i >= 0; i = i - 3) {
	  for (int j = 0; j < height; ++j) {
		  rotated[rotated_index] = input[i + (j * width * 3)];
		  rotated[rotated_index + 1] = input[i + 1 + (j * width * 3)];
		  rotated[rotated_index + 2] = input[i + 2 + (j * width * 3)];
		  rotated_index = rotated_index + 3;
	  }
  }

}
