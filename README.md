# RobocupPy
[![Build Status](https://travis-ci.org/SD-Group-17/RobocupPy.svg?branch=core_test)](https://travis-ci.org/SD-Group-17/RobocupPy) [![codecov](https://codecov.io/gh/SD-Group-17/RobocupPy/branch/core_test/graph/badge.svg)](https://codecov.io/gh/SD-Group-17/RobocupPy)

RobocupPy is a wrapper for the UT Austin Villa Codebase that allows you to use python for Robocup.

## Documentation:
* Open [html file](https://github.com/SD-Group-17/RobocupPy/tree/core_test/Documentation/html) using a browser
* [Wiki](https://github.com/SD-Group-17/RobocupPy/wiki)
  * [Robocup Class Documentation](https://github.com/SD-Group-17/RobocupPy/wiki/Robocup-Class-Documentation)
  * [UML Diagrams](https://github.com/SD-Group-17/RobocupPy/wiki/UML)

## Installation
### Installation(Singularity)
This is a quick instruction guide on how to install the Robocup distribution on your home computer.

Make sure you are connected to the internet as this will require a once off ~300mb download
#### 4.2.1 Ubuntu 18.04


## How to wrap more data for python
* To see these techniques in use view [Strategy.cc](https://github.com/SD-Group-17/RobocupPy/blob/core_test/Code_Base/behaviors/strategy.cc). the pyFunction.
* the first command that must be run before using or calling python Scripts or PyObjects is Py_Initialize(). this function basically creates a python interpreter to run python commands and files
* to run a python command use the following command PyRun_SimpleString("import os"). in this example here we are importing the os library to interpreter.
* this is an example on how you can call on a python file. to check if it has imported you can put pModule in an if statement
```C++

//calling on myFile.py 
PyObject *  pName = PyUnicode_FromString("myFile");
PyObject * pModule = PyImport_Import(pName);

if(pModule)
{
	// running the method myFunc in myFile.py
	PyObject * pFunc = PyObject_GetAttrString(pModule, "myFunc"); 
       
	if(pFunc && PyCallable_Check(pFunc))
	{
           //here we call on the python function and store the output in a PyObject in this example we are sending in a list so we attach an O before world_data
           PyObject * pReturn = PyObject_CallFunction(pFunc,"O",world_data);
	   //here we convert the pyobject to the relevent c++ format
           int x = (int) PyLong_AsLong(pReturn);
	   return x;
	}
	else
	{
            
	    cout << "ERROR: function selectSkill()\n"<<endl;
            return -1;
	}

	}
	else
	{
        
		cout << "ERROR: Module not imported"<<endl;
        return -2;
	}
```
for info on how to convert c++ to PyObject look [here](https://docs.python.org/3/c-api/arg.html)
and how to convert from PyObject to c++ you can look [here](https://docs.python.org/3/c-api/long.html)

* an example of converting a c++ data type to a python Object
```C++
//converting an integer to a PyObject
int x = 5
PyObject * temp;
temp = Py_BuildValue("i",x);
```
* an example of extracting data from a PyObject 
```C++
PyObject * objectPy;
//update objectPy
int x = (int) PyLong_AsLong(objectPy);
```

### Handling Python Lists 
* how to define a python list
```C++
int n = 5;
PyObject* pyList = PyList_New(n);
```
* how to get an item from the pyList (get the item at index 0)
```C++
PyObject* item = PyList_GetItem(pyList, 0);
```
* how to set an item in a python list
```C++
int value = 5;
PyObject * item = Py_BuildValue("i",value);
PyList_SetItem(PyList,0,item);
```
