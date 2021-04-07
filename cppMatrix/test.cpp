
#include "pch.h"
#include "CppUnitTest.h"
//#include "mymatrix.cpp"
#include "main.cpp"
#include "mymatrix.h"
#include "catch.hpp"
#include <iostream>
#include <sstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testV1
{




	void fill_rand(myMatrix &mat) {
		for (int i = 0; i < mat.numRows; ++i) {
			for (int j = 0; j < mat.numCols; ++j) {
				mat.data[i][j] = rand() % 10;
			}
		}
	}



	TEST_CLASS(MatrixTests)
	{
	public:

		
		TEST_METHOD(addMatrix) {
			int rows = rand() % 5 + 1;
			int cols = rand() % 5 + 1;

			myMatrix A(rows, cols);
			myMatrix B(rows, cols);

			fill_rand(A);
			fill_rand(B);

			myMatrix *C = A.addMatrix(B);
			//Assert::AreEqual(C->numRows == A.numRows);
			REQUIRE(C->numRows == A.numRows);
			REQUIRE(C->numCols == A.numCols);

			for (int i = 0; i < A.numRows; ++i) {
				for (int j = 0; j < A.numCols; ++j) {
					REQUIRE(C->data[i][j] == A.data[i][j] + B.data[i][j]);
				}
			}
		}
	};



	
}