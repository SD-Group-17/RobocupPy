//From commandline run:///
g++ -o Main main.cpp
./Main
//////////////////////////
expected output:
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 
3, 3, 3, 3, 3, 3, 3, 3, 3, 3,

The main.cpp file is just an example for how the classes and functions may be called.
Initialise a matrix with values using:
QSMatrix<double> myMatrix(M, N, x);
This gives M rows, N columns, with each entry initialised to the value of x
Access elements of a matrix using:
accessedElement = myMatrix(i,j);
Where i and j are the indices of desired element

To print a matrix:
cout<<endl;
cout<<addMat.printMatrix()<<endl;

Initialises 10 by 10 array of zeros:
QSMatrix<double> zeros(10,10,0.0); 

To initialise an n by n identity matrix:
QSMatrix<double> identity = anotherMatrix.identity(n);
where anotherMatrix is an arbitrary OSMatrix

Other operaters enabled:
+=
-=
*=

