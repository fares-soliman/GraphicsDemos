#include "demosaic.h"

int master_width, master_height;

int get_red_first_row(bool GorB, int w, int h, const std::vector<unsigned char>& bayer) {
	if (GorB) {
		std::vector<double> reds;

		if (h != 0) {
			//look up
			reds.push_back(bayer[(w + master_width * h) - master_width]);
		}

		if (h != master_height - 1) {
			//look down
			reds.push_back(bayer[(w + master_width * h) + master_width]);
		}

		double sum = 0.0;

		for (auto& n : reds)
			sum += n;

		double average = sum / reds.size();

		return (int)average;
	}
	else{

		if (h == 0 && w == master_width - 1) {
			//diag left down
			return bayer[(w + master_width * h) + master_width - 1];
		}

		else if (h == master_height - 1 && w == master_width - 1) {
			//diag left up
			return bayer[(w + master_width * h) - master_width - 1];
		}

		else if (h == 0) {
			//diag left down + right down
			return (bayer[(w + master_width * h) + master_width - 1] + bayer[(w + master_width * h) + master_width + 1]) / 2;
		}


		else if (h == master_height - 1) {
			//diag left up + right up
			return (bayer[(w + master_width * h) - master_width - 1] + bayer[(w + master_width * h) - master_width + 1]) / 2;
		}

		else {
			//all diags
			return (bayer[(w + master_width * h) - master_width - 1] +
					bayer[(w + master_width * h) - master_width + 1] +
					bayer[(w + master_width * h) + master_width - 1] +
					bayer[(w + master_width * h) + master_width + 1]) / 4;
		}
	}
}


int get_green_first_row(bool GorB, int w, int h, const std::vector<unsigned char>& bayer) {
	if (GorB) {
		return (bayer[(w + master_width * h)]);
	}

	else {
		std::vector<double> greens;

		if (h != 0) {
			//ontop
			greens.push_back((bayer[(w + master_width * h) - master_width]));
		}

		if (w != master_width - 1) {
			//to the right
			greens.push_back(bayer[(w + master_width * h) + 1]);
		}

		if (h != master_height - 1) {
			//below
			greens.push_back((bayer[(w + master_width * h) + master_width]));
		}

		if (w != 0) {
			//to the left
			greens.push_back((bayer[(w + master_width * h) - 1]));
		}

		double sum = 0.0;

		for (auto& n : greens)
			sum += n;

		double average = sum / greens.size();

		return (int)average;
	}
}

int get_blue_first_row(bool GorB, int w, int h, const std::vector<unsigned char>& bayer) {
	if (GorB) {
		std::vector<double> blues;

		if (w != master_width - 1) {
			//to the right
			blues.push_back(bayer[(w + master_width * h) + 1]);
		}

		if (w != 0) {
			//to the left
			blues.push_back((bayer[(w + master_width * h) - 1]));
		}

		double sum = 0.0;

		for (auto& n : blues)
			sum += n;

		double average = sum / blues.size();

		return (int)average;
	}
	else {
		return (bayer[(w + master_width * h)]);
	}
}

int get_red_second_row(bool RorG, int w, int h, const std::vector<unsigned char>& bayer) {
	if (RorG) {
		return (bayer[(w + master_width * h)]);
	}
	else {
		std::vector<double> reds;

		if (w != master_width - 1) {
			//to the right
			reds.push_back(bayer[(w + master_width * h) + 1]);
		}

		if (w != 0) {
			//to the left
			reds.push_back((bayer[(w + master_width * h) - 1]));
		}

		double sum = 0.0;

		for (auto& n : reds)
			sum += n;

		double average = sum / reds.size();

		return (int)average;
	}
}

int get_green_second_row(bool RorG, int w, int h, const std::vector<unsigned char>& bayer) {
	if (RorG) {
		std::vector<double> greens;

		if (h != 0) {
			//ontop
			greens.push_back((bayer[(w + master_width * h) - master_width]));
		}

		if (w != master_width - 1) {
			//to the right
			greens.push_back(bayer[(w + master_width * h) + 1]);
		}

		if (h != master_height - 1) {
			//below
			greens.push_back((bayer[(w + master_width * h) + master_width]));
		}

		if (w != 0) {
			//to the left
			greens.push_back((bayer[(w + master_width * h) - 1]));
		}

		double sum = 0.0;

		for (auto& n : greens)
			sum += n;

		double average = sum / greens.size();

		return (int)average;
	}
	else {
		return (bayer[(w + master_width * h)]);
	}
}

int get_blue_second_row(bool RorG, int w, int h, const std::vector<unsigned char>& bayer) {
	if (RorG) {
		if (h == 0 && w == master_width - 1) {
			//diag left down
			return bayer[(w + master_width * h) + master_width - 1];
		}

		else if (h == master_height - 1 && w == master_width - 1) {
			//diag left up
			return bayer[(w + master_width * h) - master_width - 1];
		}

		else if (h == master_height - 1 && w == 0) {
			//diag right up
			return bayer[(w + master_width * h) - master_width + 1];
		}

		else if (w == 0) {
			//diag right up + diag right down
			return (bayer[(w + master_width * h) - master_width + 1] + bayer[(w + master_width * h) + master_width + 1]) / 2;
		}

		else if (h == 0) {
			//diag left down + right down
			return (bayer[(w + master_width * h) + master_width - 1] + bayer[(w + master_width * h) + master_width + 1]) / 2;
		}

		else if (w == master_width - 1) {
			//diag left up + left down
			return (bayer[(w + master_width * h) + master_width - 1] + bayer[(w + master_width * h) - master_width - 1]) / 2;
		}

		else if (h == master_height - 1) {
			//diag left up + right up
			return (bayer[(w + master_width * h) - master_width - 1] + bayer[(w + master_width * h) - master_width + 1]) / 2;
		}

		else {
			//all diags
			return (bayer[(w + master_width * h) - master_width - 1] +
				bayer[(w + master_width * h) - master_width + 1] +
				bayer[(w + master_width * h) + master_width - 1] +
				bayer[(w + master_width * h) + master_width + 1]) / 4;
		}
	}
	else {
		std::vector<double> blues;

		if (h != 0) {
			//look up
			blues.push_back(bayer[(w + master_width * h) - master_width]);
		}

		if (h != master_height - 1) {
			//look down
			blues.push_back(bayer[(w + master_width * h) + master_width]);
		}

		double sum = 0.0;

		for (auto& n : blues)
			sum += n;

		double average = sum / blues.size();

		return (int)average;
	}
}




void demosaic(
  const std::vector<unsigned char> & bayer,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(width*height*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  ////////////////////////////////////////////////////////////////////////////

  master_height = height;
  master_width = width;

  bool GB = false;
  bool GorB = true;
  bool RorG = true;

  int rgb_iterator = 0;

  for (int h = 0; h < height; ++h) {
	  GB = !GB;
	  GorB = true;
	  RorG = true;
	  for (int w = 0; w < width; ++w) {
		  if (GB) {
			  if (GorB) {
				  rgb[rgb_iterator] = get_red_first_row(GorB, w, h, bayer);
				  rgb[rgb_iterator + 1] = bayer[w + width * h];
				  rgb[rgb_iterator + 2] = get_blue_first_row(GorB, w, h, bayer);
			  }
			  else {
				  rgb[rgb_iterator] = get_red_first_row(GorB, w, h, bayer);
				  rgb[rgb_iterator + 1] = get_green_first_row(GorB, w, h, bayer);
				  rgb[rgb_iterator + 2] = bayer[w + width * h];
			  }
			  GorB = !GorB;
		  }

		  else {
			  if (RorG) {
				  rgb[rgb_iterator] = bayer[w + width * h];
				  rgb[rgb_iterator + 1] = get_green_second_row(RorG, w, h, bayer);
				  rgb[rgb_iterator + 2] = get_blue_second_row(RorG, w, h, bayer);
			  }
			  else {
				  rgb[rgb_iterator] = get_red_second_row(RorG, w, h, bayer);
				  rgb[rgb_iterator + 1] = bayer[w + width * h];
				  rgb[rgb_iterator + 2] = get_red_second_row(RorG, w, h, bayer);
			  }
			  RorG = !RorG;
		  }
		  rgb_iterator = rgb_iterator + 3;

	  }
  }





}
