#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include<iostream>

using namespace std;
// C functions //
//==============//

long cdot(int x[],int y[])
{
    int n = sizeof(x) / sizeof(x[0]);

    int value = 0;

    for(int i = 0;i<n;i++)
    {
        value += x[i]*y[i];


    }

    return value;
}

int** cAdd(int x[3][3],int y[3][3])
{
    int n = sizeof(x)/sizeof(x[0]);
    int m = sizeof(x[0])/sizeof(x[0][0]);

    int** A;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            A[i][j] = x[i][j] + y[i][j];
        }
    }

    return A;
}

// Wrapper functions //

PyObject* dotProduct(PyObject* self,PyObject* args)
{
    int n;
    int m;
    PyObject* pyvec1;
    PyObject* pyvec2;

    if(!PyArg_ParseTuple(args,"OO",&pyvec1,&pyvec2))
    {
        return NULL;
    }

    n =  PyObject_Length(pyvec1);
    m =  PyObject_Length(pyvec2);

    if(n<0 || m<0)
    {
        return NULL;
    }

    int cvec1[n];
    int cvec2[n];

    for(int i = 0;i<n;i++)
    {
        PyObject* item1 = PyList_GetItem(pyvec1, i);
        PyObject* item2 = PyList_GetItem(pyvec2, i);

        int value1 = (int) PyLong_AsLong(item1);
        int value2 = (int) PyLong_AsLong(item2);

        cvec1[i] = value1;
        cvec2[i] = value2;
    }

    long ans = cdot(cvec1,cvec2);
    return Py_BuildValue("i",ans);
}


PyObject * add(PyObject* self,PyObject args)
{
    int n;
    int m;
    PyObject* A;
    PyObject* B;

    if(!PyArg_ParseTuple(args,"OO",&A,&B))
    {
        return NULL;
    }

    if(PyObject_Length(A)<0 || PyObject_Length(B)<0)
    {
        return NULL;
    }

    n = PyObject_Length(A);
    m = PyObject_Length(PyList_GetItem(A, 0));

    int X[3][3];
    int Y[3][3];
    int Ans[3][3];

    for(int i = 0;i<3;i++)
    {
        PyObject* row1 = PyList_GetItem(A, i);
        PyObject* row2 = PyList_GetItem(B, i);

        for(int j=0;j<3;j++)
        {
            PyObject* item1 =  PyList_GetItem(row1, j);
            PyObject* item2 =  PyList_GetItem(row2, j);

            int value1 = (int) PyLong_AsLong(item1);
            int value2 = (int) PyLong_AsLong(item2);

            X[i][j] = value1;
            Y[i][j] = value2;
        }
    }

    Ans = cAdd(X,Y);
    PyObject* Matrix;

    for(int i=0;i<n;i++)
    {
        PyObject * Row;

        for(int j=0;j<m;j++)
        {
            int value = A[i][j];
            PyList_Append(Row,Py_BuildValue("i",value));
        }

        PyList_Append(Matrix,Row);
    }

    return Matrix;
}


// Binding of wrappers

static PyMethodDef Methods[] = {
    {"dotProduct",dotProduct,METH_VARARGS,"Calculates dor product between 2 vectors"},
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
