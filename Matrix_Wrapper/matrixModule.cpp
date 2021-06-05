#define PY_SSIZE_T_CLEAN
#include <Python.h>
#include<iostream>
#include<vector>

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

vector<vector<int>> getMatrix(PyObject* pyMatrix)
{
    int n,m;

    n = PyObject_Length(pyMatrix);
    m = PyObject_Length(PyList_GetItem(pyMatrix, 0));

    vector<vector<int>> Ans(n,vector<int>(m));

    for(int i = 0;i<n;i++)
    {
        PyObject* row = PyList_GetItem(pyMatrix, i);

         for(int j=0;j<m;j++)
        {
            PyObject* item =  PyList_GetItem(row, j);
            Ans[i][j] = (int) PyLong_AsLong(item);
        }
    }

    return Ans;
}


PyObject* setMatrix(vector<vector<int>> &Matrix)
{
    int n = Matrix.size();
    int m = Matrix[0].size();

    PyObject* pyMatrix = PyList_New(n);

    for(int i=0;i<n;i++)
    {
        PyObject * Row = PyList_New(m);

        for(int j=0;j<m;j++)
        {
            int value = Matrix[i][j];
            //PyList_Append(Row,Py_BuildValue("i",value));
            PyList_SetItem(Row,j,Py_BuildValue("i",value));
        }

        //PyList_Append(pyMatrix,Row);
        PyList_SetItem(pyMatrix,i,Row);
    }

    return pyMatrix; 
}

vector<vector<int>> cAdd(vector<vector<int>> &A,vector<vector<int>> &B)
{
    int n = A.size();
    int m = A[0].size();

    vector<vector<int>> Ans(n,vector<int>(m));

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            Ans[i][j] = A[i][j] +  B[i][j]; 
        }
    }
    
    return Ans;
}

vector<vector<int>> cMultiply(vector<vector<int>> &A,vector<vector<int>> &B)
{
    int n = A.size();
    int m = A[0].size();

    int k = B.size();
    int p = B[0].size();

    if(m==k)
    {
        vector<vector<int>> Ans(n,vector<int>(p));

        for(int i = 0;i<n;i++)
        {
            for(int j = 0;j<p;j++)
            {
                int value = 0;

                for(int q = 0;q<k;q++)
                {
                    value+= A[i][q]*A[q][j];
                }

                Ans[i][j] = value;
            }
        }

        return Ans;
    }

    
}

PyObject* getIndentity(int n)
{
    vector<vector<int>> Ans(n,vector<int>(n));

    for(int i = 0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
            {
                Ans[i][j] = 1;
            }
            else
            {
                Ans[i][j] = 0;
            }
        }
    }

    return setMatrix(Ans);
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


PyObject * add(PyObject* self,PyObject* args)
{
    int n;
    int m;
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

    n = PyObject_Length(A);
    m = PyObject_Length(PyList_GetItem(A, 0));


    vector<vector<int>> M1 = getMatrix(A);
    vector<vector<int>> M2 = getMatrix(B);
    vector<vector<int>> cAns = cAdd(M1,M2);

    pyAns = setMatrix(cAns);

    return pyAns;

 }

 PyObject* multiply(PyObject* self,PyObject* args)
 {
    int n;
    int m;
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

    n = PyObject_Length(A);
    m = PyObject_Length(PyList_GetItem(A, 0));

    vector<vector<int>> M1 = getMatrix(A);
    vector<vector<int>> M2 = getMatrix(B);
    vector<vector<int>> cAns = cMultiply(M1,M2);

    pyAns = setMatrix(cAns);
    return pyAns;
    
 }


 PyObject* Eye(PyObject* self,PyObject* args)
 {
    int n;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    return getIndentity(n);
 }


// Binding of wrappers

static PyMethodDef Methods[] = {
    {"dotProduct",dotProduct,METH_VARARGS,"Calculates dor product between 2 vectors"},
    {"add",add,METH_VARARGS,"adds 2 matrices"},
    {"multiply",multiply,METH_VARARGS,"multiplies 2 matrices"},
    {"Eye",Eye,METH_VARARGS,"gets identity matrix of size nxn"},
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
