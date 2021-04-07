#include "matrix.h"
#include <iostream>

int main(int argc, char **argv) {
  QSMatrix<double> mat1(10, 10, 1.0);
  QSMatrix<double> mat2(10, 10, 2.0);
  QSMatrix<double> rectangularMatrix(10, 5, 1.0);

  QSMatrix<double> addMat = mat1 + mat2;

  QSMatrix<double> multMat = mat1 * mat2;
  QSMatrix<double> transposedMat = rectangularMatrix.transpose();
  
  //addMat.print();

  
  std::cout << "Added Matrix: "<< std::endl;
  for (int i=0; i<addMat.get_rows(); i++) {
    for (int j=0; j<addMat.get_cols(); j++) {
      std::cout << addMat(i,j) << ", ";
    }
    std::cout << std::endl;
  }
  
  
  

  return 0;
  
  
}