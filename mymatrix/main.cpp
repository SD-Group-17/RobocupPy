#include <iostream>
#include <ctime>
#include "mymatrix.h"

using namespace std;

int main()
{
    cout << "Creating A, B & C" << endl;
    myMatrix A(3,2);
    myMatrix B(2,3);
    myMatrix C(3,2);

    for(int i = 0; i < A.numRows; i++){
        for(int j = 0; j < A.numCols; j++){
            A.data[i][j] = 10*i + j;
            B.data[j][i] = 100*j + 10*i;
            C.data[i][j] = i + j;
        }
    }
    cout << "Matrix A (" << A.numRows << "x" << A.numCols << ") \n";
    A.print(cout);

    cout << "Matrix B (" << B.numRows << "x" << B.numCols << ") \n";
    B.print(cout);

    cout << "Matrix C (" << C.numRows << "x" << C.numCols << ") \n";
    C.print(cout);

    cout << "Swapping A & B" << endl;
    A.swap(B);
    cout << "Matrix A (" << A.numRows << "x" << A.numCols << ") \n";
    A.print(cout);

    cout << "Matrix B (" << B.numRows << "x" << B.numCols << ") \n";
    B.print(cout);

    cout << "Copying from A into copyA" << endl;
    myMatrix* copyA = A.copyMatrix();
    cout << "Matrix copyA (" << copyA->numRows << "x" << copyA->numCols << ") \n";
    copyA->print(cout);
    // It was allocated with new inside the function,
    // So we must delete it when we're done!!!
    delete copyA;

    cout << "sumBC = B + C" << endl;
    myMatrix* sumBC = B.addMatrix(C);
    cout << "Matrix sumBC (" << sumBC->numRows << "x" << sumBC->numCols << ") \n";
    sumBC->print(cout);
    // It was allocated with new inside the function,
    // So we must delete it when we're done!!!
    delete sumBC;

    cout << "multAC = A*C" << endl;
    myMatrix* multAC = A.multMatrix(C);
    cout << "Matrix multAC (" << multAC->numRows << "x" << multAC->numCols << ") \n";
    multAC->print(cout);
    delete multAC;

    cout << "Creating D" << endl;
    myMatrix D(2,2);
    D.data[0][0] = 1; D.data[0][1] = 2;
    D.data[1][0] = 3; D.data[1][1] = 4;
    cout << "Matrix D (" << D.numRows << "x" << D.numCols << ") \n";
    D.print(cout);

    cout << "sq = D^2" << endl;
    myMatrix* sq = D.square();
    cout << "Matrix sq (" << sq->numRows << "x" << sq->numCols << ") \n";
    sq->print(cout);

    cout << "cube = D^3 (SlowPower)" << endl;
    myMatrix* cube = D.slowPower(3);
    cout << "Matrix cube (" << cube->numRows << "x" << cube->numCols << ") \n";
    cube->print(cout);

    cout << "quad = D^4 (SlowPower)" << endl;
    myMatrix* quad = D.slowPower(4);
    cout << "Matrix cube (" << quad->numRows << "x" << quad->numCols << ") \n";
    quad->print(cout);

    // It was allocated with new inside the function,
    // So we must delete it when we're done!!!
    delete sq;
    delete cube;
    delete quad;
    cout << "sq = D^2 (FastPower)" << endl;
    sq = D.fastPower(2);
    cout << "Fast Matrix sq (" << sq->numRows << "x" << sq->numCols << ") \n";
    sq->print(cout);

    cout << "cube = D^3 (FastPower)" << endl;
    cube = D.fastPower(3);
    cout << "Fast Matrix cube (" << cube->numRows << "x" << cube->numCols << ") \n";
    cube->print(cout);

    cout << "quad = D^4 (FastPower)" << endl;
    quad = D.fastPower(4);
    cout << "Fast Matrix cube (" << quad->numRows << "x" << quad->numCols << ") \n";
    quad->print(cout);

    delete sq;
    delete cube;
    delete quad;

    cout << "Timing Slow and Fast Power" << endl;
    clock_t start;
    double diff1, diff2;
    start = clock();
    quad = D.slowPower(10000);
    diff1 = ( std::clock() - start ) / (double)CLOCKS_PER_SEC;

    start = clock();
    quad = D.fastPower(10000);
    diff2 = ( std::clock() - start ) / (double)CLOCKS_PER_SEC;

    cout<<"Slow Power: " << diff1 << "\nFase Power: " << diff2 << endl;


    return 0;
}

