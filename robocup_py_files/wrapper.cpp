#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyMethodDef Methods[] = {
    //add wrapper methods here
    
    {NULL,NULL,0,NULL}
};

static struct PyModuleDef RobocupPy= {
    PyModuleDef_HEAD_INIT,
    "RobocupPy",
    "Documentation",
    -1,
    Methods
};

PyMODINIT_FUNC 
PyInit_RobocupPy(void)
{
    return PyModule_Create(&RobocupPy);
}