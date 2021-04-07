#ifndef MYMATRIX_H
#define MYMATRIX_H

#include <iostream>

class myMatrix
{
public:
    int **data;
    int numRows;
    int numCols;

public:
    myMatrix(int nRows, int nCols);
    ~myMatrix();

    // Should swap the data values of two matrices.
    void swap(myMatrix &other);

    // Should return a new matrix that contains a copy of this one
    myMatrix* copyMatrix() const;
    // Should return a new matrix that contains the sum of this and other
    myMatrix* addMatrix(const myMatrix &other) const;
    // Should return a new matrix that contains the multiplication of this and other
    // Such that: output = this * other
    myMatrix* multMatrix(const myMatrix &other) const;

    // I've implemented this for you but it requires other functions to work
    myMatrix& operator*=(const myMatrix &other);

    // Should return a new matrix that is the square of this one.
    myMatrix* square() const;
    // Print the current matrix. \t between entries, \n between rows
    void print(std::ostream &out) const;

    // Calculate this matrix to the power of n
    myMatrix* slowPower(int n) const;
    myMatrix* fastPower(int n) const;

    // Turn the matrix into an identity matrix
    // I've done this for you
    void fillEye();
};

#endif // MYMATRIX_H
