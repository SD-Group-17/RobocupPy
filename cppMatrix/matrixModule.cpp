#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include "matrix.h"



/*  
 *  Functions for getting and Setting the PyObjects
 *
 */

QSMatrix<long int> getMatrix(PyObject * pyMatrix)
{
    int n,m;

    n = PyObject_Length(pyMatrix);
    m = PyObject_Length(PyList_GetItem(pyMatrix, 0));

    //typeof(PyLong_AsLong(PyList_GetItem(pyMatrix, 0)))
    long int x  = 0;
    QSMatrix<long int> A(n,m,x);
    
    int data[n][m];

    for(int i = 0;i<n;i++)
    {
        PyObject* row = PyList_GetItem(pyMatrix, i);

        for(int j=0;j<m;j++)
        {
            PyObject* item =  PyList_GetItem(row, j);
            data[i][j] = (int) PyLong_AsLong(item);
        }
    }


    for(int i = 0;i<n;i++)
    {
        for(int j = 0;j<m;j++)
        {
            A(i)(j) = data[i][j];
        }
    }

    return A;
}

PyObject* setMatrix(QSMatrix matrix)
{
    int n = matrix.get_rows();
    int m = matrix.get_cols();

    PyObject* pyMatrix;

    for(int i=0;i<n;i++)
    {
        PyObject * Row;

        for(int j=0;j<m;j++)
        {
            int value = matrix(i)(j);
            PyList_Append(Row,Py_BuildValue("i",value));
        }

        PyList_Append(pyMatrix,Row);
    }
}

int getRow(PyObject* pyMatrix)
{
    return PyObject_Length(pyMatrix);
}

int getCol(PyObject* pyMatrix)
{
    return PyObject_Length(PyList_GetItem(pyMatrix, 0));
}


/*
 * Wrapper Functions
 *
 */


PyObject* multiply(PyObject* self,PyObject* args)
{
    PyObject* A;
    PyObject* B;
    PyObject* pyAns;

    if(!PyArg_ParseTuple(args,"OO",&A,&B))
    {
        return NULL;
    }

    if(PyObject_Length(A)<0 || PyObject_Length(B)<0)
    {
        return NULL;
    }

    //getting dimensions
    QSMatrix<int> Mat1(getRow(A),getCol(A),0);
    QSMatrix<int> Mat2(getRow(B),getCol(B),0);
    QSMatrix<int> Ans(getRow(A),getCol(A),0);

    //setting values of matrices
    Mat1 = getMatrix(A);
    Mat2 = getMatrix(B);

    Ans = Mat1 * Mat2;
    pyAns = setMatrix(Ans);

    return pyAns;
}


static PyMethodDef Methods[] = {
    {"multiply",multiply,METH_VARARGS,"multiplies 2 matrices"},
    {NULL,NULL,0,NULL}
};

static struct PyModuleDef matrixModule = {
    PyModuleDef_HEAD_INIT,
    "matrixModule",
    "Documentation",
    -1,
    Methods
};

PyMODINIT_FUNC 
PyInit_matrixModule(void)
{
    return PyModule_Create(&matrixModule);
}