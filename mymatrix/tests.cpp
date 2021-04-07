#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "mymatrix.h"

#include <iostream>
#include <sstream>

using namespace std;

/*
 * Note that this file is FULL of memory leaks.
 *
 * Dynamically allocated matrices are not cleared after each test so that a
 * bug in the destructor does not cause strange test failures.
 *
 */
int num_mu = 0;
int num_sq = 0;
int num_op = 0;
int num_cp = 0;
int num_ad = 0;

void reset_counters(){
    num_mu = 0;
    num_sq = 0;
    num_op = 0;
    num_cp = 0;
    num_ad = 0;
}

extern "C" {
__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void *this_fn, void *call_site) {
    #pragma GCC diagnostic ignored "-Wpmf-conversions"
    if(this_fn == (void*) &myMatrix::multMatrix) {
        ++num_mu;
    }else if(this_fn == (void*) &myMatrix::copyMatrix){
        ++num_cp;
    }else if(this_fn == (void*) &myMatrix::operator*=){
        ++num_op;
    }else if(this_fn == (void*) &myMatrix::square){
        ++num_sq;
    }else if(this_fn == (void*) &myMatrix::addMatrix){
        ++num_ad;
    }
    #pragma GCC diagnostic warning "-Wpmf-conversions"
}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void *this_fn, void *call_site) {

}
}

void fill_rand(myMatrix &mat){
    for(int i = 0; i < mat.numRows; ++i){
        for(int j = 0; j < mat.numCols; ++j) {
            mat.data[i][j] = rand() % 10;
        }
    }
}

std::ostream& operator << ( std::ostream& os, myMatrix const& value ) {
    os << value.data[0][0];
    for(int c = 1; c < value.numCols; ++c){
        os << "," << value.data[0][c];
    }

    for(int r = 1; r < value.numRows; ++r){
        os << "/";
        os << value.data[r][0];
        for(int c = 1; c < value.numCols; ++c){
            os << "," << value.data[r][c];
        }
    }
    return os;
}

TEST_CASE("Matrix::Print"){
    std::stringstream ss;
    std::stringstream tr;

    myMatrix A(3,2);
    for(int i = 0; i < A.numRows; ++i){
        A.data[i][0] = rand() % 10;
        tr << A.data[i][0];
        for(int j = 1; j < A.numCols; ++j){
            A.data[i][j] = rand() % 10;
            tr << "\t" << A.data[i][j];
        }
        tr << endl;
    }

    A.print(ss);

    REQUIRE(ss.str() == tr.str());
}

TEST_CASE("Matrix::Swap"){
    // Bad Random Numbers
    int original_A_rows = rand() % 5 + 1;
    int original_B_rows = rand() % 5 + 1;
    int original_A_cols = rand() % 5 + 1;
    int original_B_cols = rand() % 5 + 1;

    myMatrix A(original_A_rows, original_A_cols);
    myMatrix B(original_B_rows, original_B_cols);

    fill_rand(A);
    fill_rand(B);

    auto pdata_A = A.data;
    auto pdata_B = B.data;

    A.swap(B);
    REQUIRE(A.numRows == original_B_rows);
    REQUIRE(A.numCols == original_B_cols);
    REQUIRE(B.numRows == original_A_rows);
    REQUIRE(B.numCols == original_A_cols);

    REQUIRE(A.data == pdata_B);
    REQUIRE(B.data == pdata_A);
}

TEST_CASE("Matrix::Copy"){
    int rows = rand() % 5 + 1;
    int cols = rand() % 5 + 1;

    myMatrix A(rows, cols);
    fill_rand(A);
    myMatrix *B = A.copyMatrix();

    REQUIRE(A.data != B->data);
    REQUIRE(A.numRows == B->numRows);
    REQUIRE(A.numCols == B->numCols);

    for(int i = 0; i < A.numRows; ++i){
        for(int j = 0; j < A.numCols; ++j){
            REQUIRE(A.data[i][j] == B->data[i][j]);
        }
    }
}

TEST_CASE("Matrix::addMatrix"){
    int rows = rand() % 5 + 1;
    int cols = rand() % 5 + 1;

    myMatrix A(rows, cols);
    myMatrix B(rows, cols);

    fill_rand(A);
    fill_rand(B);

    myMatrix *C = A.addMatrix(B);

    REQUIRE(C->numRows == A.numRows);
    REQUIRE(C->numCols == A.numCols);

    for(int i = 0; i < A.numRows; ++i){
        for(int j = 0; j < A.numCols; ++j){
            REQUIRE(C->data[i][j] == A.data[i][j] + B.data[i][j]);
        }
    }
}

TEST_CASE("Matrix::multMatrix"){
    int d1 = rand() % 5 + 2;
    int d2 = rand() % 5 + 2;
    int d3 = rand() % 5 + 2;

    myMatrix A(d1, d2);
    myMatrix B(d2, d3);

    fill_rand(A);
    fill_rand(B);

    myMatrix *C = A.multMatrix(B);
    REQUIRE(C->numRows == A.numRows);
    REQUIRE(C->numCols == B.numCols);

    for(int i = 0; i < A.numRows; ++i){
        for(int j = 0; j < B.numCols; ++j){
            int correct_value = 0;
            for(int k = 0; k < d2; ++k){
                correct_value += A.data[i][k]*B.data[k][j];
            }

            REQUIRE(C->data[i][j] == correct_value);
        }
    }


    SECTION("Square"){
        int n = rand() % 5 + 2;

        myMatrix A(n,n);
        fill_rand(A);

        myMatrix *actual = A.multMatrix(A);
        myMatrix *result = A.square();

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                REQUIRE(actual->data[i][j] == result->data[i][j]);
            }
        }
    }

    SECTION("SlowPower"){
        int n = rand() % 5 + 2;
        int pow = rand() % 3 + 2;

        myMatrix original(n,n);
        fill_rand(original);

        myMatrix *correct = original.copyMatrix();
        for(int p = 1; p < pow; ++p){
            myMatrix *tmp = correct->multMatrix(original);
            tmp->swap(*correct);
        }

        reset_counters();
        myMatrix *result = original.slowPower(pow);

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(correct->data[i][j] != result->data[i][j]){
                    CAPTURE( original );
                    CAPTURE( pow );
                    CAPTURE( *result );
                    CAPTURE( *correct  );

                    FAIL("Incorrect result.");
                }
            }
        }

        if(num_mu > pow - 1){
            FAIL("Power = " << pow << ", SlowPower performed " << num_mu
                 << " matrix multiplications, expected no more than " << pow - 1);
        }

    }

    SECTION("FastPower"){
        int n = rand() % 5 + 2;
        int pow = rand() % 10 + 15;

        myMatrix original(n,n);
        fill_rand(original);

        myMatrix *correct = original.copyMatrix();
        for(int p = 1; p < pow; ++p){
            myMatrix *tmp = correct->multMatrix(original);
            tmp->swap(*correct);
        }

        reset_counters();
        myMatrix *result1 = original.slowPower(pow);
        int slow_mults = num_mu;

        reset_counters();
        myMatrix *result = original.fastPower(pow);
        int fast_mults = num_mu;

        int tmp = pow, popcnt = 0, maxpow = 0;
        while(tmp > 0){
            popcnt += (tmp % 2);
            tmp /= 2;
            ++maxpow;
        }

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                if(correct->data[i][j] != result->data[i][j]){
                    CAPTURE( original );
                    CAPTURE( pow );
                    CAPTURE( *result );
                    CAPTURE( *correct  );

                    FAIL("Incorrect result.");
                }
            }
        }

        if(fast_mults > popcnt + maxpow) {
            FAIL("Power = " << pow << ", FastPower performed " << fast_mults
                 << " matrix multiplications, expected no more than " << (maxpow + popcnt));
        }
    }
}
