#define PY_SSIZE_T_CLEAN
#include <Python.h>

static PyMethodDef Methods[] = {
    //add wrapper methods here
    
    {NULL,NULL,0,NULL}
};

static struct PyModuleDef Robocup= {
    PyModuleDef_HEAD_INIT,
    "Robocup",
    "Documentation",
    -1,
    Methods
};

PyMODINIT_FUNC 
PyInit_Robocup(void)
{
    return PyModule_Create(&Robocup);
}