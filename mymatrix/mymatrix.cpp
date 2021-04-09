#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "mymatrix.h"
#include <iostream>

using namespace std;

/**
 * @brief myMatrix::myMatrix
 * @param nRows Number of rows in the matrix
 * @param nCols Number of columns in the matrix
 *
 * Constructor
 * This function should allocate the memory required to store the data.
 */
myMatrix::myMatrix(int nRows, int nCols) : numRows(nRows), numCols(nCols){
    data = new int*[numRows];
    for(int i = 0; i < numRows; i++)
        data[i] = new int[numCols];
}

// need to figure out how to wrap constructor
static PyObject* py_myMatrix(PyObject* self, PyObject* args)
{
    // int n;

    // if(!PyArg_ParseTuple(args,"i",&n))
    // {
    //     return NULL;
    // }

    // return Py_BuildValue("i",myMatrix(n));
}


/**
 * @brief myMatrix::~myMatrix
 * Destructor
 * This function should free the memory allocated by the constructor.
 */
myMatrix::~myMatrix(){
    for(int i = 0; i < numRows; i++)
        delete [] data[i];
    delete[] data;
}

// what do we do with the destructor?

/**
 * @brief myMatrix::swap
 * @param other The matrix with which to swap data values
 *
 * Swaps the values of two matrices.
 *
 * Hint: Do this by manipulating pointers, NOT by copying the actual data!
 */
void myMatrix::swap(myMatrix &other)
{
    int trow,tcol;
}

/**
 * @brief myMatrix::copyMatrix
 * @return Allocates and returns a pointer to a new matrix that has copies of the data in this one.
 *
 * Remember to copy the individual items, not just pointers!
*/
myMatrix* myMatrix::copyMatrix() const{

}

/**
 * @brief myMatrix::addMatrix
 * @param other Matrix with which to add this one
 * @return A new matrix that is the sum of this and other
 *
 * This function shouldn't change either of the original matrices!
 */
myMatrix* myMatrix::addMatrix(const myMatrix &other) const
{
    //dimension for this matrix
    int m = sizeof(this->data)/ sizeof(this->data[0]);
    int n = sizeof(this->data[0])/ sizeof(this->data[0][0]);

    myMatrix * A = new myMatrix(m,n);

    for(int i = 0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            A->data[i][j] = this->data[i][j] + other.data[i][j];
        }
    }

    return A;

}

static PyObject* py_addMatrix(PyObject* self, PyObject* args)
{
    // int n;

    // if(!PyArg_ParseTuple(args,"i",&n))
    // {
    //     return NULL;
    // }

    // return Py_BuildValue("i",addMatrix(n));
}

/**
 * @brief myMatrix::multMatrix
 * @param other
 * @return this*other
 *
 * Calculates the value of this matrix multiplied by other.
 * The data should be saved to a new matrix.
 *
 */
myMatrix* myMatrix::multMatrix(const myMatrix &other) const{


    int m;
    int n;
    int x;
    int y;
    float sum;
    myMatrix* A;

    //dimension for this matrix
    m = sizeof(this->data)/ sizeof(this->data[0]); //row
    n = sizeof(this->data[0])/ sizeof(this->data[0][0]); //column

    //dimension of other matrix
    x = sizeof(other.data)/ sizeof(other.data[0]); //row
    y = sizeof(other.data[0])/ sizeof(other.data[0][0]); //column

    if(n==x)
    {
        A = new myMatrix(m,y);
        for (int i = 0; i < m ; i++)
        {
            for(int j = 0; j<y;j++)
            {
                sum = 0;

                for(int k=0;k<n;i++)
                {
                    sum+= this->data[i][k] * other.data[k][j];
                }

                A->data[i][j] = sum;
            }
        }

        return  A;
    }


}

static PyObject* py_multMatrix(PyObject* self, PyObject* args)
{
    // int n;

    // if(!PyArg_ParseTuple(args,"i",&n))
    // {
    //     return NULL;
    // }

    // return Py_BuildValue("i",multMatrix(n));
}

/**
 * @brief myMatrix::square
 * @return Returns the current matrix to the power of 2.
 *
 * Remember that you need to do matrix multiplication, not just square the elements.
 */
myMatrix* myMatrix::square() const
{
   //dimension for this matrix
    int m = sizeof(this->data)/ sizeof(this->data[0]); //row
    int n = sizeof(this->data[0])/ sizeof(this->data[0][0]); //column

    myMatrix * B = new myMatrix(m,n);
    B->data = this->data;

    myMatrix * A = this->multMatrix(*B);
    return A;
}

static PyObject* py_square(PyObject* self, PyObject* args)
{
    // int n;

    // if(!PyArg_ParseTuple(args,"i",&n))
    // {
    //     return NULL;
    // }

    // return Py_BuildValue("i",square(n));
}

/**
 * @brief myMatrix::print
 * Print the current matrix to out.
 * Use out, the same way that you'd use cout...eg: out << "Hello World!" << endl;
 *
 * Items should be separated by \t and there should be a \n at the end of each row.
 * Make sure that you don't output \t\n at the end of each row though!
 */
void myMatrix::print(std::ostream &out) const{

}

/**
 * @brief slowPower
 * @param n
 * @return Returns a new matrix of this one to the power of n.
 *
 * Implement this function by repeatedly multiplying a temp matrix by this one.
 */
myMatrix* myMatrix::slowPower(int n) const{

}

/**
 * @brief myMatrix::fastPower
 * @param n
 * @return Returns a new matrix of this one to the power of n.
 *
 * Implement this function using the algorithm from the lab 1 handout!
 */
myMatrix* myMatrix::fastPower(int n) const{

}
/**
 * @brief myMatrix::fillEye
 * Turn the matrix into an identity matrix.
 */
void myMatrix::fillEye(){
    for(int i = 0; i < numRows; i++)
        for(int j = 0; j < numCols; j++)
            data[i][j] = (i==j);
}

static PyObject* py_fillEye(PyObject* self, PyObject* args)
{
    // int n;

    // if(!PyArg_ParseTuple(args,"i",&n))
    // {
    //     return NULL;
    // }

    // return Py_BuildValue("i",fillEye(n));
}

/**
 * @brief myMatrix::operator *=
 * @param other
 * @return Updates the current matrix so that this = this*other
 */
myMatrix& myMatrix::operator *=(const myMatrix &other){
    myMatrix* temp = this->multMatrix(other);

    this->swap(*temp);
    delete temp;

    return *this;
}

// how do you wrap operators??

// Wrapper overhead
static PyMethodDef myMethods[] = {
    {"myMatrix",py_myMatrix,METH_VARARGS,"Constructor"},
    {"addMatrix",py_addMatrix,METH_VARARGS,"Add two matrices"},
    {"multMatrix",py_multMatrix,METH_VARARGS,"Multiply two matrices"},
    {"square",py_square,METH_VARARGS,"Multiply a matrix by itself"},
    {"fillEye",py_fillEye,METH_VARARGS,"Turn matrix into identity matrix"},
    {NULL,NULL,0,NULL}
};

static struct PyModuleDef myMatrix = {
    PyModuleDef_HEAD_INIT,
    "myMatrix",
    "Documentation",
    -1,
    myMethods
};

PyMODINIT_FUNC 
PyInit_myModule(void)
{
    return PyModule_Create(&myMatrix);
}
