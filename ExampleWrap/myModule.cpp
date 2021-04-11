#define PY_SSIZE_T_CLEAN
#include <Python.h>

int Cfib(int n)
{
    if(n<2)
    {
        return n;
    }
    else
    {
        return Cfib(n-1) + Cfib(n-2);
    }
}

int cAdd(int x,int y)
{
    return x+y;
}

//wrapper function for integer
static PyObject* fib(PyObject* self, PyObject* args)
{
    int n;

    if(!PyArg_ParseTuple(args,"i",&n))
    {
        return NULL;
    }

    return Py_BuildValue("i",Cfib(n));
}

static PyObject* add(PyObject* self, PyObject* args)
{
    int x;
    int y;

     if(!PyArg_ParseTuple(args,"ii",&x,&y))
     {
         return NULL;
     }

     return Py_BuildValue("i",cAdd(x,y));
}


static PyMethodDef myMethods[] = {
    {"fib",fib,METH_VARARGS,"Calculates the fibonacci numbers"},
    {"add",add,METH_VARARGS,"add 2 numbers"},
    {NULL,NULL,0,NULL}
};

static struct PyModuleDef myModule = {
    PyModuleDef_HEAD_INIT,
    "myModule",
    "Documentation",
    -1,
    myMethods
};

PyMODINIT_FUNC 
PyInit_myModule(void)
{
    return PyModule_Create(&myModule);
}