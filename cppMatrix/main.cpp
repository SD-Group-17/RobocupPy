#include "matrix.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
  QSMatrix<double> mat1(3, 3, 1.0);
  QSMatrix<double> mat2(3, 2, 2.0);
  QSMatrix<double> rectangularMatrix(3, 2, 10.0);
  QSMatrix<double> zeros(10,10,0.0); //initialises 10 by 10 array of zeros

  //QSMatrix<double> addMat = mat1 + mat2;
  //QSMatrix<double> multMat = mat1 * mat2;
  // 
  QSMatrix<double> transposedMat = rectangularMatrix.transpose();
  QSMatrix<double> identity(4,6,0.0); //initialise empty 4by8 matrix
  identity.setIdentity(); //identity is a function on the QSMatrix class, so it has to be called on a random QS matrix. Dunno how to make it work better


  //addMat(0,0) = -1;
  cout<< "Mat1: "<< mat1.get_rows() << ':'  << mat1.get_cols() <<endl;
  cout<< "Mat2: "<< mat2.get_rows() << ':'  << mat2.get_cols() <<endl;

  QSMatrix<double> multTest = transposedMat *rectangularMatrix;

  cout<<"X^T:"<<endl;
  cout<<transposedMat.printMatrix()<<endl;
  cout<<"X:"<<endl;

  cout<<rectangularMatrix.printMatrix()<<endl;
  
  
  cout<<"X^T * X:"<<endl;

  cout<<multTest.printMatrix()<<endl;


  
  

  
  return 0;
  
  
}