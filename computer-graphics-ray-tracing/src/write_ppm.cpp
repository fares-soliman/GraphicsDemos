#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>
using namespace std;


bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code from computer-graphics-raster-images
    assert(
        (num_channels == 3 || num_channels == 1) &&
        ".ppm only supports RGB or grayscale images");
    ////////////////////////////////////////////////////////////////////////////
    // Replace with your code here:

    ofstream output(filename);

    if (num_channels == 3) {
        output << "P3" << endl;
        output << to_string(width) << " " << to_string(height) << endl;
        output << "255" << endl;

        for (int i = 0; i < width * height * 3; i = i + 3) {
            output << (int)data[i] << " ";
            output << (int)data[i + 1] << " ";
            output << (int)data[i + 2] << " ";
            output << endl;
        }

        output.close();
    }

    else {
        output << "P2" << endl;
        output << to_string(width) << " " << to_string(height) << endl;
        output << "255" << endl;

        for (int i = 0; i < width * height; ++i) {
            output << (int)data[i];
            output << endl;
        }

        output.close();
    }


    return true;
  ////////////////////////////////////////////////////////////////////////////
}
