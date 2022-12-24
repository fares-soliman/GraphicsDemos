#include "write_obj.h"
#include <fstream>
#include <cassert>
#include <iostream>
using namespace std;

bool write_obj(
  const std::string & filename,
  const Eigen::MatrixXd & V,
  const Eigen::MatrixXi & F,
  const Eigen::MatrixXd & UV,
  const Eigen::MatrixXi & UF,
  const Eigen::MatrixXd & NV,
  const Eigen::MatrixXi & NF)
{
  assert((F.size() == 0 || F.cols() == 3 || F.cols() == 4) && "F must have 3 or 4 columns");
  
  ofstream output(filename);

  for (int i = 0; i < V.rows(); ++i) {
	  output << "v" << " ";
	  output << V(i, 0) << " ";
	  output << V(i, 1) << " ";
	  output << V(i, 2) << endl;
  }

  for (int i = 0; i < UV.rows(); ++i) {
	  output << "vt" << " ";
	  output << UV(i, 0) << " ";
	  output << UV(i, 1) << endl;
  }

  for (int i = 0; i < NV.rows(); ++i) {
	  output << "vn" << " ";
	  output << NV(i, 0) << " ";
	  output << NV(i, 1) << " ";
	  output << NV(i, 2) << endl;
  }

  for (int i = 0; i < F.rows(); ++i) {
	  output << "f" << " ";
	  output << F(i, 0) << "/" << UF(i, 0) << "/" << NF(i, 0) << " " 
			 << F(i, 1) << "/" << UF(i, 1) << "/" << NF(i, 1) << " "
			 << F(i, 2) << "/" << UF(i, 2) << "/" << NF(i, 2) << " "
			 << F(i, 3) << "/" << UF(i, 3) << "/" << NF(i, 3) << endl;
  }

  output.close();
  return true;

}
