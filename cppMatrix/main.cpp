#include "matrix.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  QSMatrix<double> mat1(10, 10, 1.0);
  QSMatrix<double> mat2(10, 10, 2.0);
  QSMatrix<double> rectangularMatrix(10, 5, 1.0);
  QSMatrix<double> zeros(10,10,0.0); //initialises 10 by 10 array of zeros

  QSMatrix<double> addMat = mat1 + mat2;

  QSMatrix<double> multMat = mat1 * mat2;
  QSMatrix<double> transposedMat = rectangularMatrix.transpose();
  QSMatrix<double> identity = zeros.identity(2); //identity is a function on the QSMatrix class, so it has to be called on a rendom QS matrix. Dunno how to make it work better


  addMat(0,0) = -1;
  cout<<endl;
  cout<<identity.printMatrix()<<endl;

  
  return 0;
  
  
}